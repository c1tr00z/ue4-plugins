// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <functional>

/**
 * 
 */
class ASSISTUTILS_API AssistArrayUtils
{
public:
public:

	template <typename T>
	static TArray<T> Where(TArray<T> ItemsArray, std::function<bool(T)> Selector)
	{
		TArray<T> ReturnValues;
		if (ItemsArray.Num() > 0)
		{
			T DefaultValue = {};
			for (T Item : ItemsArray)
			{
				if (Item != DefaultValue && Selector(Item))
				{
					ReturnValues.Add(Item);
				}
			}
		}
		return ReturnValues;
	}

	template <typename T>
	static TArray<T> SelectNotNull(TArray<T> ItemsArray)
	{
		T DefaultValue = {};
		if (ItemsArray.Num() == 0)
		{
			return ItemsArray;
		}

		TArray<T> NotNull;
		for (T Item : ItemsArray)
		{
			if (Item != DefaultValue)
			{
				NotNull.Add(Item);
			}
		}

		return NotNull;
	}

	template <typename T>
	static T First(TArray<T> ItemsArray)
	{
		TArray<T> NotNull = SelectNotNull(ItemsArray);
		if (NotNull.Num() == 0)
		{
			return {};
		}

		return NotNull[0];
	}

	template <typename T>
	static T RandomItemArray(TArray<T> ItemsArray)
	{
		if (ItemsArray.Num() == 0)
		{
			return {};
		}
		return ItemsArray[FMath::RandRange(0, ItemsArray.Num() - 1)];
	}

	template <typename T>
	static T RandomItemSet(TSet<T> ItemsSet)
	{
		return RandomItemArray(ItemsSet.Array());
	}

	template <typename T1, typename T2>
	static TArray<T2> Select(TArray<T1> ItemsArray, std::function<T2(T1)> Selector)
	{
		TArray<T2> ReturnValues;
		for (T1 Item : ItemsArray)
		{
			ReturnValues.Add(Selector(Item));
		}
		return ReturnValues;
	}

	template <typename T1, typename T2>
	static TArray<T2> SelectFromSet(TSet<T1> ItemsSet, std::function<T2(T1)> Selector)
	{
		return Select(ItemsSet.Array(), Selector);
	}

	template <typename T>
	static TArray<T> Copy(TArray<T> From)
	{
		TArray<T> Copied;
		for (T Item : From)
		{
			Copied.Add(Item);
		}
		return Copied;
	}

	template <typename T>
	static int32 Sum(TArray<T> Items, std::function<int32(T)> Selector)
	{
		int32 Value = 0;
		for (T Item : Items)
		{
			Value += Selector(Item);
		}
		return Value;
	}

	template <typename T>
	static void Foreach(TArray<T> Items, std::function<void(T)> Function)
	{
		for (T Item : Items)
		{
			Function(Item);
		}
	}

	template <typename T>
	static TArray<T> AddRange(TArray<T> Items, TArray<T> NewItems)
	{
		for (T Item : NewItems)
		{
			Items.Add(Item);
		}
		return Items;
	}
};
