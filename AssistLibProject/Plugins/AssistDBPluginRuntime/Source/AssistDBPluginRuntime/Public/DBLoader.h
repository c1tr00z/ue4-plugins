// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "DB.h"
#include "Runtime/Engine/Classes/Engine/StreamableManager.h"
#include "DBItem.h"

/**
 * 
 */
class ASSISTDBPLUGINRUNTIME_API DBLoader
{
public:
	DBLoader();
	~DBLoader();

	static UDB* GetDB();

	template<typename T>
	static TArray<T*> GetItems();

	template<typename T>
	static T* Load(FString path);

	template<typename T>
	static T* Load(UObject* object, FString key);

	static UClass * LoadBPClass(UDBItem * item, FString key);

private:
	static UDB* DB;
};

template<typename T>
inline TArray<T*> DBLoader::GetItems()
{
	TArray<T*> itemsArray;

	if (DBLoader::DB == nullptr)
	{
		DBLoader::DB = GetDB();//UDB::GetDB();
	}

	if (DBLoader::DB == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("DB is null"));
		return itemsArray;
	}

	TArray<UDBItem*> Items = DBLoader::DB->Items;

	auto max = Items.Num();
	for (int i = 0; i < max; ++i) {
		T* item = Cast<T>(Items[i]);
		if (item != nullptr) {
			itemsArray.Add(item);
		}
	}

	return itemsArray;
}

template<typename T>
inline T * DBLoader::Load(FString Path)
{
	FStreamableManager AssetLoader;
	FStringAssetReference AssetRef(Path);
	auto Asset = AssetRef.TryLoad(); //AssetLoader.SynchronousLoad(AssetRef);

	UE_LOG(LogTemp, Warning, TEXT("Path: %s"), *Path);

	if (Asset == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Asset not found"));
		return nullptr;
	}

	T* Required = Cast<T>(Asset);

	if (Required == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Asset is not T"));
		return nullptr;
	}

	return Required;
}

template<typename T>
inline T * DBLoader::Load(UObject * object, FString key)
{
	FStringAssetReference AssetRef(object);

	FString Path = object->GetPathName().LeftChop(object->GetName().Len() + 1).Append(FString(TEXT("+"))).Append(key);

	return Load<T>(Path);
}
