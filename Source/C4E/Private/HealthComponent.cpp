#include "HealthComponent.h"

#include "Math/UnitConversion.h"

UHealthComponent::UHealthComponent()
{
	_MaxHealth = 100.f;
}



void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	_CurrentHealth = _MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

	
	
}

void UHealthComponent::DamageTaken(AActor* damagedActor, float damage, const UDamageType* damageType,
	AController* instigator, AActor* causer)
{
	const float change = FMath::Min( _CurrentHealth, damage);
	_CurrentHealth -= change;
	UE_LOG(LogTemp, Display, TEXT("Damaged for %f, %f health remaining"), change, _CurrentHealth);
	if(_CurrentHealth == 0.0f) {UE_LOG(LogTemp, Display, TEXT("Dead"));}
}




