// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DBPluginCommands.h"

#define LOCTEXT_NAMESPACE "FDBPluginModule"

void FDBPluginCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "DBPlugin", "Bring up DBPlugin window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
