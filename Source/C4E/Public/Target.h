#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Target.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTargetDestroyedSignature, AController*, delegateInstigator, int, yargetValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTargetDestroyedSignature,AActor*, target, AController*, delegateInstigator);

class UHealthComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class C4E_API UTarget : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UTarget();

	UPROPERTY(BlueprintAssignable)
	FTargetDestroyedSignature OnTargetDestroyed;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _PointsValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _HealthComp;
	

private:
	UFUNCTION()
	void Handle_Dead(AController* causer);
	
};
