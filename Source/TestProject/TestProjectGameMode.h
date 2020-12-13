// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestProjectGameMode.generated.h"

UCLASS(minimalapi)
class ATestProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UMG_Game")
        void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
    virtual void BeginPlay() override;
public:
    UPROPERTY(EditAnywhere, Category = "UMG_Game")
    UUserWidget* CurrentWidget;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
        TSubclassOf<UUserWidget> StartingWidgetClass;

public:
	ATestProjectGameMode();
};



