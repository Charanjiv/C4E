#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "C4EChar.generated.h"

class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class AWeapon_Base;

UCLASS(Abstract)
class C4E_API AC4EChar : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess= "true"))
	TObjectPtr<UCameraComponent> _Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess= "true"));
	TObjectPtr<USceneComponent> _WeaponAttachPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=TextCreate_InputAttachmentRead, meta=(AllowPrivateAccess="true"))
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=TextCreate_InputAttachmentRead, meta=(AllowPrivateAccess="true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=TextCreate_InputAttachmentRead, meta=(AllowPrivateAccess="true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=TextCreate_InputAttachmentRead, meta=(AllowPrivateAccess="true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=TextCreate_InputAttachmentRead, meta=(AllowPrivateAccess="true"))
	UInputAction* ShootAction;
public:

	AC4EChar();

	UFUNCTION(BlueprintNativeEvent)
	void Init();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeapon_Base> _DefaultWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> _FireableRef;
	
	

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Shoot();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	class UAIPerceptionStimuliSourceComponent* StimulusSorce;

	void SetupStimulusSource();
};
