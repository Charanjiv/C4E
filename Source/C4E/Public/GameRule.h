#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameRule.generated.h"

	//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameRuleCompleteSignature);
	//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameRulePointsScoredSignature, AController*, scorer, int, points);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameRuleCompleteSignature, class UGameRule*, rule);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameRulePointsScoredSignature, AController*, scorer, int, points);

	UCLASS(Abstract, ClassGroup=(Custom), meta = (BlueprintSpawnableComponent))
	class C4E_API UGameRule : public UActorComponent
	{
		GENERATED_BODY()

	public:

		UGameRule();

		FGameRuleCompleteSignature OnGameRuleCompleted;
		FGameRulePointsScoredSignature OnGameRulePointsScored;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool _IsOptional;

		UFUNCTION()
		virtual void Init();

	protected:
		void BroadcastGameRuleCompleted();
		void BroadcastGameRulePointsScored(AController* scorer, int points);

};

