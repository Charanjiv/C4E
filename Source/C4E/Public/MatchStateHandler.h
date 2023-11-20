// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MatchStateHandler.generated.h"


UINTERFACE(MinimalAPI)
class UMatchStateHandler : public UInterface
{
	GENERATED_BODY()
};


class C4E_API IMatchStateHandler
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void Handle_MatchStarted();

	UFUNCTION(BlueprintNativeEvent)
	void Handle_MatchEnded();
	
};
