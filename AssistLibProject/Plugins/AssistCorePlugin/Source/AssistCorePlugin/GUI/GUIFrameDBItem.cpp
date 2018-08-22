// Fill out your copyright notice in the Description page of Project Settings.

#include "GUIFrameDBItem.h"
#include "DBLoader.h"


UClass* UGUIFrameDBItem::GetFrameClass()
{
	UClass * ClassYou = DBLoader::LoadBPClass(this, "Frame");
	if (ClassYou == nullptr || ClassYou == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("NULL GUI CLASS"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GUI FRAME IS %s"), *ClassYou->GetFullName());
	}
	return ClassYou;
}

FString UGUIFrameDBItem::GetWidgetClassPath()
{
	return GetPathByKey(FString(TEXT("Frame")));
}
