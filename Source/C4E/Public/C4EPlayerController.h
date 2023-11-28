#pragma once

#include "CoreMinimal.h"
#include "MatchStateHandler.h"
#include "GameFramework/PlayerController.h"
#include "C4EPlayerController.generated.h"

class UUserWidget_HUD;
class UInputMappingContext;

UCLASS(Abstract)
class C4E_API AC4EPlayerController : public APlayerController, public IMatchStateHandler
{
	GENERATED_BODY()

public:
	AC4EPlayerController();

	UFUNCTION(BlueprintNativeEvent)
	void Init();

	void AddScore(int amount);

	virtual void Handle_MatchStarted_Implementation() override;
	virtual void Handle_MatchEnded_Implementation() override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<APawn> _PawnToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget_HUD> _HUDWidgetClass;
	TObjectPtr<UUserWidget_HUD> _HUDWidget;

	int _Score;


};
