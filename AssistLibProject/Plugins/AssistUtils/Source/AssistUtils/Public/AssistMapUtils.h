// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <functional>

/**
 * 
 */
class ASSISTUTILS_API AssistMapUtils
{
public:
public:
	template<typename KeyType, typename ValueType>
	static TArray<KeyType> Keys(TMap<KeyType, ValueType> ItemsMap)
	{
		TArray<KeyType> Keys;
		if (ItemsMap.Num() == 0)
		{
			return Keys;
		}
		KeyType DefaultKeyValue = {};
		for (TPair<KeyType, ValueType> Pair : ItemsMap)
		{
			if (Pair.Key != DefaultKeyValue)
			{
				Keys.Add(Pair.Key);
			}
		}
		return Keys;
	}

	template<typename KeyType, typename ValueType>
	static TArray<ValueType> Values(TMap<KeyType, ValueType> ItemsMap)
	{
		TArray<ValueType> Values;
		if (ItemsMap.Num() == 0)
		{
			return Values;
		}
		ValueType DefaultValue = {};
		for (auto& Pair : ItemsMap)
		{
			if (Pair.Value != DefaultValue)
			{
				Values.Add(Pair.Value);
			}
		}
		return Values;
	}

	template<typename ItemType, typename KeyType, typename ValueType>
	static TMap<KeyType, ValueType> ToMap(TArray<ItemType> ItemsArray, std::function<KeyType(ItemType)> KeySelector, std::function<ValueType(ItemType)> ValueSelector)
	{
		TMap<KeyType, ValueType> Map;
		for (ItemType Item : ItemsArray)
		{
			Map.Add(KeySelector(Item), ValueSelector(Item));
		}
		return Map;
	}
};
