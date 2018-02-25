// Fill out your copyright notice in the Description page of Project Settings.

#include "AssistGameInstance.h"


UAssistGameInstance::UAssistGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Gui = this->CreateDefaultSubobject<AGUI>(TEXT("GUI"));
	Gui->AssistGameInstance = this;
}

