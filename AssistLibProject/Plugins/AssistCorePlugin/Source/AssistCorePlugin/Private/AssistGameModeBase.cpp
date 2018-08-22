// Fill out your copyright notice in the Description page of Project Settings.

#include "AssistGameModeBase.h"

UAssistGameInstance* AAssistGameModeBase::GetAssistGameInstance()
{
	return Cast<UAssistGameInstance>(GetGameInstance());
}

AGUI* AAssistGameModeBase::GetGUI()
{
	return GetAssistGameInstance()->GetGUI();
}


