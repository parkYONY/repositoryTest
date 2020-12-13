// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainUI.h"
#include "ProjectilInfoUI.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UProjectilInfoUI : public UMainUI
{
	GENERATED_BODY()

public:
	void UIInitalize() override;
	void SetGageData(float value);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* ProgressBarUI;
};
