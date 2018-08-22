// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/SlateCore/Public/Input/Reply.h"
#include "Runtime/Engine/Classes/Engine/ObjectLibrary.h"
#include "ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FAssistDBPluginModule : public IModuleInterface
{
public:

	UObjectLibrary * ObjectLibrary;

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();

	FReply CollectDB();
	
private:

	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};