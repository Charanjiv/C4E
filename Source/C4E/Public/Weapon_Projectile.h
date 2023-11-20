#pragma once

#include "CoreMinimal.h"
#include "Weapon_Base.h"
#include "C4E/C4EProjectile.h"
#include "GameFramework/Actor.h"
#include "Weapon_Projectile.generated.h"

UCLASS(Abstract)
class C4E_API AWeapon_Projectile : public AWeapon_Base
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AC4EProjectile> _Projectile;

public:
	virtual bool Fire_Implementation() override;
};
