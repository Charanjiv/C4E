#include "BTTask_FindPathPoint.h"

#include "NPC.h"
#include "NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPathPoint::UBTTask_FindPathPoint(FObjectInitializer const& ObjectInitializer):
UBTTask_BlackboardBase{ObjectInitializer}
{
	NodeName = TEXT("Find Path Point");
	
}

EBTNodeResult::Type UBTTask_FindPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//attempt to get npc controller
	if(auto const cont =Cast<ANPC_AIController>(OwnerComp.GetAIOwner()))
	{
		//get blackboard component from behaviour tree
		if(auto*const bc = OwnerComp.GetBlackboardComponent())
		{
			// get current patrol path index from blackboard
			auto const Index = bc->GetValueAsInt((GetSelectedBlackboardKey()));

			if(auto*npc = Cast<ANPC>(cont->GetPawn()))
			{
				//get current patrol path vector from npc
				auto const Point = npc->GetPatrolPath()->GetPatrolPoint(Index);

				//turn local vector to global point
				auto const GlobalPoint = npc->GetPatrolPath()->GetActorTransform().TransformPosition(Point);
				bc->SetValueAsVector(PatrolPathVectorKey.SelectedKeyName, GlobalPoint);

				//finish with success
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
		
	}
	return EBTNodeResult::Failed;
}
