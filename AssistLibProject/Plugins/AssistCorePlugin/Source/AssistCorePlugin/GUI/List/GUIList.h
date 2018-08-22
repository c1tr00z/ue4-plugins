// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GUI/List/GUIListItem.h"
#include "GUIList.generated.h"

/**
 * 
 */
UCLASS()
class ASSISTCOREPLUGIN_API UGUIList : public UUserWidget
{
	GENERATED_BODY()
//properties:
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGUIListItem> ListItemClass;

private:

	UPROPERTY(VisibleAnywhere)
	TArray<UObject*> Items;
	UPROPERTY(VisibleAnywhere)
	TArray<UGUIListItem*> ActiveItems;
	UPROPERTY(VisibleAnywhere)
	TArray<UGUIListItem*> InactiveItems;

protected:

//functions
private:

protected:
	
public:

	UFUNCTION(BlueprintCallable)
	void SetItems(TArray<UObject*> NewItems);
	
	UFUNCTION(BlueprintNativeEvent, Category = "Assist/GUI")
	void E_AddListItem(UGUIListItem* ListItem);
};
