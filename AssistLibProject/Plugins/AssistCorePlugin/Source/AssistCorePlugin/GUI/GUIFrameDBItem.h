// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DBItem.h"
#include "GUIFrame.h"
#include "GUIFrameDBItem.generated.h"

/**
 * 
 */
UCLASS()
class ASSISTCOREPLUGIN_API UGUIFrameDBItem : public UDBItem
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool StackIt = true;

protected:
	
public:
	UFUNCTION(BlueprintCallable)
	UClass * GetFrameClass();
	
	FString GetWidgetClassPath();
};