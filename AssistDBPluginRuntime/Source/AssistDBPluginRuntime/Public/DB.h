// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DBItem.h"
#include "DB.generated.h"

/**
 * 
 */
UCLASS()
class ASSISTDBPLUGINRUNTIME_API UDB : public UDBItem
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DB")
	TArray<UDBItem*> Items;
};
