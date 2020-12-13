// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainUI.h"
#include "GameUI.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UGameUI : public UMainUI
{
	GENERATED_BODY()

public:
	UGameUI(const FObjectInitializer& ObjectInitializer);

	void UIInitalize() override;
	void ChangeGageData(float value);
	void temp();
	
public:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget));
	//class UProjectilInfoUI* ProjectileUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* ProgressBarUI;	
};
