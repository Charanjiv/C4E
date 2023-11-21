// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "C4EGameMode.generated.h"

class UGameRule;

UCLASS(minimalapi, Abstract)
class AC4EGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AC4EGameMode();
	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

protected:
	TArray<TObjectPtr<AActor>> _PlayerStarts;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<AController>> _PlayerControllers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=MatchManagement)
	int _CountdownTimer;

	int _GameRulesLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TObjectPtr<UGameRule>, bool> _GameRuleManagers;

	FTimerHandle _TimDecreaseCountdown;
	UFUNCTION()
	
	void DecreaseCountdown();
	UFUNCTION()
	void Handle_GameRuleCompleted(UGameRule* rule);
	UFUNCTION()
	void Handle_GameRulePointsScored(AController* scorer, int points);
	

	virtual void BeginPlay() override;

	virtual void HandleMatchIsWaitingToStart() override;
	virtual void HandleMatchHasStarted() override;
	virtual void HandleMatchHasEnded() override;

	virtual void OnMatchStateSet() override;

	virtual bool ReadyToStartMatch_Implementation() override;
	virtual bool ReadyToEndMatch_Implementation() override;
};



