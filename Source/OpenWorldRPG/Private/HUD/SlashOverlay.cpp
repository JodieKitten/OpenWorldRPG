// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SlashOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void USlashOverlay::SetHealthBarPercent(float Percent)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(Percent);
	}
}

void USlashOverlay::SetStaminaBarPercent(float Percent)
{
	if (StaminaProgressBar)
	{
		StaminaProgressBar->SetPercent(Percent);
	}
}

int32 USlashOverlay::SetGoldCount(int32 Gold)
{
	if (GoldCount)
	{
		//turns number into text from string
		const FString String = FString::Printf(TEXT("%d"), Gold);
		const FText Text = FText::FromString(String);
		GoldCount->SetText(Text);
	}
	return int32();
}

int32 USlashOverlay::SetSoulsCount(int32 Souls)
{
	if (SoulsCount)
	{
		//turns number into text from string
		const FString String = FString::Printf(TEXT("%d"), Souls);
		const FText Text = FText::FromString(String);
		SoulsCount->SetText(Text);
	}
	return int32();
}
