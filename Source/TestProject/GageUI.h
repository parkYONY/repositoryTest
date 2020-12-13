// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectilUI.h"
#include "GageUI.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UGageUI : public UProjectilUI
{
	GENERATED_BODY()

public:
	void Initailize() override;

	void SetProgressBar(UProgressBar* bar);
	void SetGageValue(float value);

private:
	UPROPERTY()
	class UProgressBar* BarUI;

};
