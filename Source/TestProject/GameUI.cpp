// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUI.h"
#include "ProjectilInfoUI.h"
#include "Components/ProgressBar.h"
#include "TestProjectCharacter.h"

UGameUI::UGameUI(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}
void UGameUI::UIInitalize()
{
	//ProjectileUIClass->Player = this->Player;
	//ProjectileUIClass->UIInitalize();	
	//ChangeGageData(Player->GageTime);
	ProgressBarUI = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBarUI")));
	UE_LOG(LogTemp, Warning, TEXT("gameuiint"));
}
void UGameUI::ChangeGageData(float value)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Input Value : Float : %f"), value));
	if (ProgressBarUI != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("progressbar"));
		ProgressBarUI->SetPercent(value);
	}
}
void UGameUI::temp()
{
	ProgressBarUI->SetPercent(1.0f);
}