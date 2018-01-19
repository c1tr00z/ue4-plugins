// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "DBPluginStyle.h"

class FDBPluginCommands : public TCommands<FDBPluginCommands>
{
public:

	FDBPluginCommands()
		: TCommands<FDBPluginCommands>(TEXT("DBPlugin"), NSLOCTEXT("Contexts", "DBPlugin", "DBPlugin Plugin"), NAME_None, FDBPluginStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};