#include "C4EGameMode.h"

#include "C4EPlayerController.h"
#include "GameRule.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"



AC4EGameMode::AC4EGameMode()
	: Super()
{
	_CountdownTimer = 3;
	_GameRulesLeft = 0;
}

AActor* AC4EGameMode::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if(_PlayerStarts.Num() == 0)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), _PlayerStarts);
	}
	if(_PlayerStarts.Num() >0)
	{
		return _PlayerStarts[0];
	}
	return nullptr;
}

void AC4EGameMode::PostLogin(APlayerController* NewPlayer)
{
	_PlayerControllers.AddUnique(NewPlayer);
	if(AC4EPlayerController* castedPC = Cast<AC4EPlayerController>(NewPlayer))
	{
		//TODO; bind to relevant events
		castedPC->Init();
	}
	
	Super::PostLogin(NewPlayer);
}

void AC4EGameMode::Logout(AController* Exiting)
{
	_PlayerControllers.Remove(Exiting);
	Super::Logout(Exiting);
}

void AC4EGameMode::DecreaseCountdown()
{
	_CountdownTimer--;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%d"), _CountdownTimer));
	if(_CountdownTimer == 0)
	{
		StartMatch();
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(_TimeDecreaseCountdown, this, &AC4EGameMode::DecreaseCountdown, 1.f, false);
	}
}

void AC4EGameMode::Handle_GameRuleCompleted(UGameRule* rule)
{
	if(*_GameRuleManagers.Find(rule)) {return;}

	_GameRulesLeft--;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black,
		FString::Printf(TEXT("GameRule completed. %d Remaining"), _GameRulesLeft));
	if(_GameRulesLeft != 0){return;}

	EndMatch();
}

void AC4EGameMode::Handle_GameRulePointsScored(AController* scorer, int points)
{
	
}

void AC4EGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> outComponents;
	GetComponents(outComponents);
	for(UActorComponent* comp: outComponents)
	{
		if(UGameRule* rule = Cast<UGameRule>(comp))
		{
			_GameRuleManagers.Add(rule, rule->_IsOptional);
			rule->Init();
			rule->OnGameRuleCompleted.AddDynamic(this, &AC4EGameMode::Handle_GameRuleCompleted);
			rule->OnGameRulePointsScored.AddDynamic(this, &AC4EGameMode::AC4EGameMode::Handle_GameRulePointsScored);
			if(!rule->_IsOptional)
			{
				_GameRulesLeft++;
			}
		}
	}
}

void AC4EGameMode::HandleMatchIsWaitingToStart()
{
	GetWorld()->GetTimerManager().SetTimer(_TimeDecreaseCountdown, this, &AC4EGameMode::DecreaseCountdown, 1.f, false);
	Super::HandleMatchIsWaitingToStart();
}

void AC4EGameMode::HandleMatchHasStarted()
{
	for(AController* controller : _PlayerControllers)
	{
		if(UKismetSystemLibrary::DoesImplementInterface(controller, UMatchStateHandler::StaticClass()))
		{
			IMatchStateHandler::Execute_Handle_MatchStarted(controller);
		}
	}
	Super::HandleMatchHasStarted();
}

void AC4EGameMode::HandleMatchHasEnded()
{
	for(AController* controller : _PlayerControllers)
	{
		if(UKismetSystemLibrary::DoesImplementInterface(controller, UMatchStateHandler::StaticClass()))
		{
			IMatchStateHandler::Execute_Handle_MatchEnded(controller);
		}
	}
	Super::HandleMatchHasEnded();
}

void AC4EGameMode::OnMatchStateSet()
{
	FString output;
	if(MatchState == MatchState::WaitingToStart)
	{
		output = "Waiting to Start";
	}
	else if(MatchState==MatchState::InProgress)
	{
		output = "In Progress";
	}
	else if(MatchState==MatchState::WaitingPostMatch)
	{
		output = "Waiting post match";
	}
	else if(MatchState==MatchState::LeavingMap)
	{
		output = "Leaving Map";
	}
	GEngine->AddOnScreenDebugMessage(-1,5.F,FColor::Turquoise, FString::Printf(TEXT("State changed To: %s"), *output));
	
	Super::OnMatchStateSet();
}

bool AC4EGameMode::ReadyToStartMatch_Implementation()
{
	return false;
}

bool AC4EGameMode::ReadyToEndMatch_Implementation()
{
	return false;
}
