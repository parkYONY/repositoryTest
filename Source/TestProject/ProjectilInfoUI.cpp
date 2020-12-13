// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectilInfoUI.h"
#include "Components/ProgressBar.h"
#include "TestProjectCharacter.h"

void UProjectilInfoUI::UIInitalize()
{	
	ProgressBarUI = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBarUI")));
	SetGageData(Player->GageTime);
}
void UProjectilInfoUI::SetGageData(float value)
{
	if (ProgressBarUI != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("progressbar"));
		ProgressBarUI->SetPercent(value);
	}	
}