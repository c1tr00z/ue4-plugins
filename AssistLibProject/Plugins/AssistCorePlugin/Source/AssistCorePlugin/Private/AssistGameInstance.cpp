// Fill out your copyright notice in the Description page of Project Settings.

#include "AssistGameInstance.h"
#include "Runtime/Engine/Classes/Engine/World.h"

UAssistGameInstance::UAssistGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

AGUI * UAssistGameInstance::GetGUI()
{
	if (Gui == nullptr || Gui == NULL)
	{
		Gui = Cast<AGUI>(GetWorld()->SpawnActor(GuiClass));
	}
	
	return Gui;
}