#include "C4EChar.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Fireable.h"
#include "Weapon_Base.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AC4EChar::AC4EChar()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);

	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(GetCapsuleComponent());
	_Camera->SetRelativeLocation(FVector(-10.f,0.f,60.f));
	_Camera->bUsePawnControlRotation = true;

	_WeaponAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponAttachPoint"));
	_WeaponAttachPoint->SetupAttachment(_Camera);
	
}

void AC4EChar::Init_Implementation()
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
	
}



void AC4EChar::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	if(Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(),MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AC4EChar::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2d>();
	if(Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
	
}

void AC4EChar::Shoot()
{
	if(_FireableRef)
	{
		IFireable::Execute_Fire(_FireableRef);
	}
}

void AC4EChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AC4EChar::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AC4EChar::Look);

		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AC4EChar::Shoot);
		
	}
}
