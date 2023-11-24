// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameRule.h"
#include "GameRule_Target.generated.h"

class UTarget;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class C4E_API UGameRule_Target : public UGameRule
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGameRule_Target();

	virtual void Init() override;

protected:
UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UTarget>> _Targets;

	int _AmountRemaining;

	UFUNCTION()
	void Handle_TargetDestroyed(AController* causer, int targetValue);
	

};
