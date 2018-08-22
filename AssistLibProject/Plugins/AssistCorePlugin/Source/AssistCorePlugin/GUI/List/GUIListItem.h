// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GUIListItem.generated.h"

class UGUIList;

/**
 * 
 */
UCLASS()
class ASSISTCOREPLUGIN_API UGUIListItem : public UUserWidget
{
	GENERATED_BODY()
	
//properties
private:

	UPROPERTY()
	UObject* Item;

protected:

public:

	UPROPERTY()
	UGUIList* List;

//functions
private:

protected:

public:
	void SetItem(UObject* NewItem);

	UFUNCTION(BlueprintCallable)
	UObject* GetItem();
	
};
