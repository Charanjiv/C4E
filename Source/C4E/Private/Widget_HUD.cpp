﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_HUD.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UWidget_HUD::NativeConstruct()
{
	Super::NativeConstruct();

	if(HealthBar)
	{
		HealthBar->SetPercent(0.f);
	}
	if(ScoreText)
	{
		ScoreText->SetText(FText::FromString("Score: 0"));
	}
}

void UWidget_HUD::UpdateHealth(float newHealthRatio)
{
	if(HealthBar)
	{
		HealthBar->SetPercent(newHealthRatio);
	}
}

void UWidget_HUD::UpdateScore(int newScore)
{
	if(ScoreText)
	{
		ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"),newScore)));
	}
}