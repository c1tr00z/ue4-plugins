// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Public/EngineUtils.h"

/**
 * 
 */
class ASSISTUTILS_API AssistActorsUtils
{
public:
public:
	template <typename T>
	static TArray<T*> FindActorsByTypeOnScene(UWorld* World)
	{
		TArray<T*> Requireds;
		for (TActorIterator<AActor> ActorItr(World); ActorItr; ++ActorItr)
		{
			T* Required = Cast<T>(*ActorItr);
			if (Required)
			{
				Requireds.Add(Required);
			}
		}
		return Requireds;
	}
};
