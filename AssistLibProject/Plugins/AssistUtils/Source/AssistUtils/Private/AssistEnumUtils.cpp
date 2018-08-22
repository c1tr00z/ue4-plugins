// Fill out your copyright notice in the Description page of Project Settings.

#include "AssistEnumUtils.h"

FString AssistEnumUtils::ToString(TCHAR * EnumName, uint8 EnumValue)
{
	UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, EnumName, true);
	FString EnumValueString;
	if (!EnumPtr)
	{
		EnumValueString.Empty();
	}
	else
	{
		EnumValueString = EnumPtr->GetDisplayNameTextByValue(EnumValue).ToString();
	}

	return EnumValueString;
}
