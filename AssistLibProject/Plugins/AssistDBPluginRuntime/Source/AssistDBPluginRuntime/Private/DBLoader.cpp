// Fill out your copyright notice in the Description page of Project Settings.

#include "DBLoader.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

UDB* DBLoader::DB = nullptr;

DBLoader::DBLoader()
{
}

DBLoader::~DBLoader()
{
}

UDB * DBLoader::GetDB()
{
	return Load<UDB>(FString(TEXT("/Game/DB/DB")));
}

UClass * DBLoader::LoadBPClass(UDBItem * item, FString key)
{
	if (item == nullptr || !IsValid(item))
	{
		UE_LOG(LogTemp, Error, TEXT("Item cant be null"));
	}
	FString FullAssetName = item->GetName().Append(FString(TEXT("+"))).Append(key);
	FString ClassName = FString::Printf(TEXT("%s.%s_C"), *FullAssetName, *FullAssetName); 
	FString Path = item->GetPathName().LeftChop((item->GetName().Len() * 2) + 1).Append(ClassName);

	UClass* Result = FindObject<UClass>(ANY_PACKAGE, *Path);

	if (Result == nullptr) {
		Result = StaticLoadClass(UObject::StaticClass(), nullptr, *Path, nullptr, LOAD_None, nullptr);
	}

	return Result;
}

