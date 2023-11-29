#include "BTTask_IncrementPathIndex.h"

#include "NPC.h"
#include "NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_IncrementPathIndex::UBTTask_IncrementPathIndex(FObjectInitializer const& ObjectInitializer):
UBTTask_BlackboardBase{ObjectInitializer}
{
	NodeName = TEXT("Increment Path Index");
}

EBTNodeResult::Type UBTTask_IncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get ai controller
	if(auto* const Cont = Cast<ANPC_AIController>(OwnerComp.GetAIOwner()))
	{
		//get NPC
		if(auto* const NPC = Cast<ANPC>(Cont->GetPawn()))
		{
			if(auto* const BC = OwnerComp.GetBlackboardComponent())
			{
				auto const NoOfPoints = NPC->GetPatrolPath()->Num();
				auto const MinIndex = 0;
				auto const MaxIndex = NoOfPoints - 1;
				auto Index = BC->GetValueAsInt(GetSelectedBlackboardKey());

				//change direction if at first or last index if in bidirectional mode
				if(bBiDirectional)
				{
					if(Index >= MaxIndex && Direction == EDirectionType::Forward)
					{
						Direction = EDirectionType::Reverse;
					}
					else if(Index ==MinIndex && Direction == EDirectionType::Reverse)
					{
						Direction = EDirectionType::Forward;
					}
				}

				//write new value of index to blackboard
				BC->SetValueAsInt(GetSelectedBlackboardKey(),
					(Direction== EDirectionType::Forward ? ++ Index : --Index) % NoOfPoints);

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
		
	}
	return EBTNodeResult::Failed;
}
