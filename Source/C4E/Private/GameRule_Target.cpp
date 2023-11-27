﻿#include "GameRule_Target.h"

#include "Target.h"
#include "Kismet/GameplayStatics.h"


UGameRule_Target::UGameRule_Target()
{
	
}

void UGameRule_Target::Init()
{
	if(_Targets.Num() == 0)
	{
		TArray<AActor*> outActors;
		UGameplayStatics:: GetAllActorsWithTag(GetWorld(), FName("GameRuleTarget"), outActors);
		for(AActor* a : outActors)
		{
			_Targets.Add(Cast<UTarget>(a->GetComponentByClass(UTarget::StaticClass())));
			
		}
	}

	_AmountRemaining = _Targets.Num();
	for(UTarget* target: _Targets)
	{
		target->OnTargetDestroyed.AddDynamic(this, &UGameRule_Target::Handle_TargetDestroyed);
	}
	Super::Init();
}

void UGameRule_Target::Handle_TargetDestroyed(AActor* target, AController* causer)
{
	_AmountRemaining--;
	BroadcastGameRulePointsScored(causer,1);
	if(_AmountRemaining == 0)
	{
		BroadcastGameRuleCompleted();
	}
}
