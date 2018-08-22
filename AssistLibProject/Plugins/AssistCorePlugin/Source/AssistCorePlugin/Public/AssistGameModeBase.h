// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GUI.h"
#include "AssistGameInstance.h"
#include "AssistGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ASSISTCOREPLUGIN_API AAssistGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	UAssistGameInstance * GetAssistGameInstance();

	UFUNCTION(BlueprintCallable)
	AGUI * GetGUI();
	
};
