// Fill out your copyright notice in the Description page of Project Settings.

#include "DBItem.h"



FString UDBItem::GetPathByKey(FString Key)
{
	FString FullAssetName = this->GetName().Append(FString(TEXT("+"))).Append(Key);
	FString ClassName = FString::Printf(TEXT("%s.%s_C"), *FullAssetName, *FullAssetName);
	FString Path = this->GetPathName().LeftChop((this->GetName().Len() * 2) + 1).Append(ClassName);
	return Path;
}
