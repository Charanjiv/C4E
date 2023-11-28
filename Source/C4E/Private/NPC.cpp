#include "NPC.h"

#include "Fireable.h"
#include "Weapon_Base.h"
#include "Components/CapsuleComponent.h"

#include "Kismet/KismetSystemLibrary.h"


ANPC::ANPC()
{

	PrimaryActorTick.bCanEverTick = true;
	_WeaponAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponAttachPoint"));
	_WeaponAttachPoint->SetupAttachment(GetCapsuleComponent());

}


void ANPC::BeginPlay()
{
	if(_DefaultWeapon)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = this;
		TObjectPtr<AActor> spawnedGun = GetWorld()->SpawnActor(_DefaultWeapon, &_WeaponAttachPoint->GetComponentTransform(), spawnParams);
		spawnedGun->AttachToComponent(_WeaponAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
		if(UKismetSystemLibrary::DoesImplementInterface(spawnedGun, UFireable::StaticClass()))
		{
			_FireableRef = spawnedGun;
		}
	}
	Super::BeginPlay();
	
}


void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UBehaviorTree* ANPC::GetBehaviourTree() const
{
	return Tree;
}

