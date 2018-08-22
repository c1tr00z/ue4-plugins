// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AssistDBPluginCommands.h"

#define LOCTEXT_NAMESPACE "FAssistDBPluginModule"

void FAssistDBPluginCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "AssistDBPlugin", "Bring up AssistDBPlugin window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
