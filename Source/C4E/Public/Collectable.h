
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCollectableSignature, class ACollectable*, subject, AController*, causer);
class USphereComponent;

UCLASS(Abstract)
class C4E_API ACollectable : public AActor
{
	GENERATED_BODY()
                                 
public:

	ACollectable();
	UPROPERTY(BlueprintAssignable)
	FCollectableSignature OnCollected;
	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> _Collision;

	UFUNCTION(BlueprintCallable)
	void BroadcastCollected(AController* causer);

	
	

	


};
