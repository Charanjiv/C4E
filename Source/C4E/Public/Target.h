// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Target.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTargetDestroyedSignature, AController*, delegateInstigator, int, yargetValue);

class UHealthComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class C4E_API UTarget : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTarget();

	UPROPERTY(BlueprintAssignable)
	FTargetDestroyedSignature OnTargetDestroyed;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _PointsValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _HealthComp;
	
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void Handle_Dead(AController* causer);
	
};
