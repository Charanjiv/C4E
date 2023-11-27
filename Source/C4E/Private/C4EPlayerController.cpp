// Fill out your copyright notice in the Description page of Project Settings.


#include "C4EPlayerController.h"

#include "C4EChar.h"
#include "EnhancedInputSubsystems.h"
#include "UserWidget_HUD.h"
#include "Blueprint/UserWidget.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"


AC4EPlayerController::AC4EPlayerController() : Super()
{
}

void AC4EPlayerController::Init_Implementation()
{

	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	
	if(_HUDWidgetClass)
	{
		_HUDWidget = CreateWidget<UUserWidget_HUD, AC4EPlayerController*>(
			this, _HUDWidgetClass.Get());
		_HUDWidget->AddToViewport();
	}

	if(GetPawn() != nullptr)
	{
		GetPawn()->Destroy();
	}
}


void AC4EPlayerController::Handle_MatchStarted_Implementation()
{
	UWorld* const world = GetWorld();

	AActor* tempStart = UGameplayStatics::GetGameMode(world)->FindPlayerStart(this);
	FVector spawnLocation = tempStart != nullptr ? tempStart->GetActorLocation() : FVector::ZeroVector;
	FRotator spawnRotation = tempStart != nullptr ? tempStart->GetActorRotation() :FRotator::ZeroRotator;
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	APawn* tempPawn = world->SpawnActor<APawn>(_PawnToSpawn, spawnLocation, spawnRotation, spawnParams);
	Possess(tempPawn);

	if(AC4EChar* castedPawn = Cast<AC4EChar>(tempPawn))
	{
		
		castedPawn->Init();
	}
}

void AC4EPlayerController::Handle_MatchEnded_Implementation()
{
	//SetInputMode(FInputModeUIOnly());
	
}


