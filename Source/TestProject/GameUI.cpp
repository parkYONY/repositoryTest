// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUI.h"
#include "ProjectilInfoUI.h"

void UGameUI::UIInitalize()
{
	ProjectileUIClass->Player = this->Player;
	ProjectileUIClass->UIInitalize();
}
void UGameUI::ChangeGageData(float value)
{
	ProjectileUIClass->SetGageData(value);
}