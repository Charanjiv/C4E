#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Fireable.generated.h"


UINTERFACE()
class UFireable : public UInterface
{
	GENERATED_BODY()
};

class C4E_API IFireable
{
	GENERATED_BODY()

	
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool Fire();
	
};
