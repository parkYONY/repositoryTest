// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectilUI.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "GageUI.h"

UProjectilUI::UProjectilUI(const FObjectInitializer& Initializer) : 
	Super(Initializer)
{
	//borderbtn = Cast<UBorder>(GetWidgetFromName(TEXT("Borderbtn")));
	//if (borderbtn != nullptr)
	//{
	//	borderbtn->OnMouseButtonDownEvent.BindUFunction(this, TEXT("OnResetButtonClicked"));
	//}
	//TArray<UWidget*> widgets;
	//WidgetTree->GetAllWidgets(widgets);
}
void UProjectilUI::Initailize()
{	
	UE_LOG(LogTemp, Warning, TEXT("UProjectilUI"));		
	//GageClass = NewObject<UGageUI>(UProjectilUI::StaticClass());
	//if (GageClass)
	//{
	//	GageClass->Initailize();
	//}		
}
void UProjectilUI::NativeConstruct()
{
	Super::NativeConstruct();		
	UE_LOG(LogTemp, Warning, TEXT("native"));
	
	if (WidgetTree)
	{		
		TArray<UWidget*> Widgets;
		WidgetTree->GetAllWidgets(Widgets);

		for (UWidget* Widget : Widgets)
		{
			if (Widget && Widget->IsA(UButton::StaticClass()))
			{
				//if (UButton* Btn = Cast<UButton>(Widget))
				//{
				//	FScriptDelegate Del;
				//	Del.BindUFunction(this, TEXT("PlayBtnOnClickSound"));
				//	Btn->OnClicked.Add(Del);
				//}
				ResetButton = Cast<UButton>(GetWidgetFromName(TEXT("ResetBtn")));
				if (ResetButton)
				{
					ResetButton->OnClicked.AddDynamic(this, &UProjectilUI::OnResetButtonClicked);
				}
			}
			if (Widget && Widget->IsA(UProgressBar::StaticClass()))
			{
				ProgressBarUI = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBarUI")));
				if (ProgressBarUI)
				{							
					//GageClass = NewObject<UGageUI>(UProjectilUI::StaticClass());
					//if (GageClass)
					//{
					//	GageClass->Initailize();
					//	GageClass->SetProgressBar(ProgressBarUI);
					//}
				}
			}
		}
	}
}
void UProjectilUI::NativePreConstruct()
{
	Super::NativePreConstruct();
}
void UProjectilUI::OnResetButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("push"));
}
void UProjectilUI::SetGage(float value)
{				
	if (ProgressBarUI != nullptr)
	{
		ProgressBarUI->SetPercent(value);
	}
/*	if (gageclass)
	{		
		gengine->addonscreendebugmessage(-1, 5.0f, fcolor::red, fstring::printf(text("input value : float : %f"), value));
		gageclass->setgagevalue(value);
	}	*/	
}
