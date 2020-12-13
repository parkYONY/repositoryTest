// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectilUI.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "TestProjectCharacter.h"

UProjectilUI::UProjectilUI(const FObjectInitializer& Initializer) : 
	Super(Initializer)
{
}
void UProjectilUI::Init(ATestProjectCharacter* player)
{	
	UE_LOG(LogTemp, Warning, TEXT("UProjectilUI"));		
	Player = player;	
}
void UProjectilUI::NativeConstruct()
{
	Super::NativeConstruct();		
	UE_LOG(LogTemp, Warning, TEXT("native"));	

	ResetButton = Cast<UButton>(GetWidgetFromName(TEXT("ResetButton")));
	if (ResetButton)
	{
		ResetButton->OnClicked.AddDynamic(this, &UProjectilUI::OnResetButtonClicked);
	}
	ProgressBarUI = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBarUI")));
	//if (WidgetTree)
	//{		
	//	TArray<UWidget*> Widgets;
	//	WidgetTree->GetAllWidgets(Widgets);

	//	for (UWidget* Widget : Widgets)
	//	{
	//		if (Widget && Widget->IsA(UButton::StaticClass()))
	//		{
	//			//ResetButton = Cast<UButton>(GetWidgetFromName(TEXT("ResetBtn")));
	//			//if (ResetButton)
	//			//{
	//			//	ResetButton->OnClicked.AddDynamic(this, &UProjectilUI::OnResetButtonClicked);
	//			//}
	//		}
	//		if (Widget && Widget->IsA(UProgressBar::StaticClass()))
	//		{
	//			//ProgressBarUI = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBarUI")));
	//			//if (ProgressBarUI != nullptr)
	//			//{
	//			//	
	//			//	//ProgressBarUI->PercentDelegate.BindUFunction(this, "GetGageData");
	//			//}				
	//		}
	//	}
	//}
}
void UProjectilUI::OnResetButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("reset"));
}
void UProjectilUI::SetGage(float value)
{								
	if (ProgressBarUI != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("gage~~"));
		ProgressBarUI->SetPercent(value);
	}
/*	if (gageclass)
	{		
		gengine->addonscreendebugmessage(-1, 5.0f, fcolor::red, fstring::printf(text("input value : float : %f"), value));
		gageclass->setgagevalue(value);
	}	*/	
}
