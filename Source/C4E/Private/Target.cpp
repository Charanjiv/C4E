// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"

#include "HealthComponent.h"


// Sets default values for this component's properties
UTarget::UTarget()
{
	_PointsValue = 1;
}


// Called when the game starts
void UTarget::BeginPlay()
{
	Super::BeginPlay();

	AActor* owner = GetOwner();
	_HealthComp = owner->FindComponentByClass<UHealthComponent>();
	if(_HealthComp == nullptr)
	{
		_HealthComp = NewObject<UHealthComponent>(owner, TEXT("Health"));
		owner->AddInstanceComponent( _HealthComp);
		_HealthComp->RegisterComponent();
		_HealthComp->OnHealthComponentDead.AddDynamic(this, &UTarget::Handle_Dead);
		owner->Modify();
	}
	owner->Tags.Add(FName("GameRuleTarget"));

	_HealthComp->OnHealthComponentDead.AddDynamic(this, &UTarget::Handle_Dead);
}

void UTarget::Handle_Dead(AController* causer)
{
	OnTargetDestroyed.Broadcast(causer, _PointsValue);
	GetOwner()->Destroy();
}




