// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "AssistDBPluginStyle.h"

class FAssistDBPluginCommands : public TCommands<FAssistDBPluginCommands>
{
public:

	FAssistDBPluginCommands()
		: TCommands<FAssistDBPluginCommands>(TEXT("AssistDBPlugin"), NSLOCTEXT("Contexts", "AssistDBPlugin", "Assist DBPlugin Plugin"), NAME_None, FAssistDBPluginStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};