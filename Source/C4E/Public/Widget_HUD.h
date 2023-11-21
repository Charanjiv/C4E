﻿#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_HUD.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS(Abstract, BlueprintType)
class C4E_API UWidget_HUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void UpdateHealth(float newHealthRatio);
	void UpdateScore(int newScore);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ScoreText;
};