// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GUI.h"
#include "AssistGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ASSISTCOREPLUGIN_API UAssistGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UAssistGameInstance(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AGUI* Gui;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AGUI> GuiClass;

public:

	UFUNCTION(BlueprintCallable)
	AGUI* GetGUI();
};
