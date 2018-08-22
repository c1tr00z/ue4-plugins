// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"

#define TEST_BIT(Bitmask, Bit) (((Bitmask) & (1 << static_cast<uint32>(Bit))) > 0)

/**
 * 
 */
class ASSISTUTILS_API AssistEnumUtils
{
public:
public:
	static FString ToString(TCHAR* EnumName, uint8 EnumValue);
};
