// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProjectilUI.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UProjectilUI : public UUserWidget
{
	GENERATED_BODY()

public:	
	UProjectilUI(const FObjectInitializer& Initializer);

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	
	virtual void Initailize();	

	UFUNCTION()
	void OnResetButtonClicked();
	void SetGage(float value);	
	float InputTime;
	
private:

	UPROPERTY(VisibleAnywhere)
		class UGageUI* GageClass;

	UPROPERTY(meta = (BindWidget))
	class UButton* ResetButton;

	UPROPERTY(meta=(BindWidget))
	class UProgressBar* ProgressBarUI;	

	//UPROPERTY(VisibleAnywhere)
	//class UGageUI* gageBar;
};
