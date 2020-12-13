// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestProjectGameMode.h"
#include "TestProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

ATestProjectGameMode::ATestProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
void ATestProjectGameMode::BeginPlay()
{
	Super::BeginPlay();
    //UE_LOG(LogTemp, Warning, TEXT("CurrentWidget0"));
	ChangeMenuWidget(StartingWidgetClass);
}
void ATestProjectGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
    //UE_LOG(LogTemp, Warning, TEXT("none"));
    if (CurrentWidget != nullptr)
    {
        //UE_LOG(LogTemp, Warning, TEXT("CurrentWidget1"));
        CurrentWidget->RemoveFromViewport();
        CurrentWidget = nullptr;
    }

    if (NewWidgetClass != nullptr)
    {
        CurrentWidget = CreateWidget(GetWorld(), NewWidgetClass);
        if (CurrentWidget != nullptr)
        {
            //UE_LOG(LogTemp, Warning, TEXT("CurrentWidget2"));
            CurrentWidget->AddToViewport();
        }
    }
}
