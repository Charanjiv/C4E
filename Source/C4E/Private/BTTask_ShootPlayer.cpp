// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ShootPlayer.h"

#include "Fireable.h"
#include "NPC.h"

UBTTask_ShootPlayer::UBTTask_ShootPlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Shoot Player");
}

EBTNodeResult::Type UBTTask_ShootPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
		
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
