// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DBItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ASSISTDBPLUGINRUNTIME_API UDBItem : public UDataAsset
{
	GENERATED_BODY()
	
public:

	FString GetPathByKey(FString Key);
};
