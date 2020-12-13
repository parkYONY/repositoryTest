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
	
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void Init(ATestProjectCharacter* player);

	UFUNCTION()
	void OnResetButtonClicked();
	void SetGage(float value);		
	
private:
	//UPROPERTY(meta = (BindWidget))
	//class UGageUI* GageClass;

	UPROPERTY(meta = (BindWidget))
	class UButton* ResetButton;

	UPROPERTY(meta=(BindWidget))
	class UProgressBar* ProgressBarUI;

	UPROPERTY(VisibleAnywhere)
	class ATestProjectCharacter* Player;	

	//UPROPERTY(VisibleAnywhere)
	//class UGageUI* gageBar;
};
