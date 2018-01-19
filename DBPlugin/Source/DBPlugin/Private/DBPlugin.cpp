// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DBPlugin.h"
#include "DBPluginStyle.h"
#include "DBPluginCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "SButton.h"
#include "DBPluginRuntime/Public/DBItem.h"
#include "DBPluginRuntime/Public/DB.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

static const FName DBPluginTabName("DBPlugin");

#define LOCTEXT_NAMESPACE "FDBPluginModule"

void FDBPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FDBPluginStyle::Initialize();
	FDBPluginStyle::ReloadTextures();

	FDBPluginCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FDBPluginCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FDBPluginModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FDBPluginModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FDBPluginModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(DBPluginTabName, FOnSpawnTab::CreateRaw(this, &FDBPluginModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FDBPluginTabTitle", "DBPlugin"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FDBPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FDBPluginStyle::Shutdown();

	FDBPluginCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(DBPluginTabName);
}

TSharedRef<SDockTab> FDBPluginModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText ButtonText = FText::FromString("Collect DB");

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SButton)
				.Text(ButtonText)
				.OnClicked_Raw(this, &FDBPluginModule::CollectDB)
			]
		];
}

void FDBPluginModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(DBPluginTabName);
}

FReply FDBPluginModule::CollectDB()
{
	if (ObjectLibrary == NULL)
	{
		ObjectLibrary = UObjectLibrary::CreateLibrary(UDBItem::StaticClass(), false, GIsEditor);
		ObjectLibrary->AddToRoot();
	}
	ObjectLibrary->LoadAssetDataFromPath(TEXT("/Game/DB"));
	ObjectLibrary->LoadAssetsFromAssetData();
	TArray<FAssetData> AssetDatas;
	ObjectLibrary->GetAssetDataList(AssetDatas);

	UDB* DB = nullptr;
	TArray<UDBItem*> Items;

	for (int32 i = 0; i < AssetDatas.Num(); ++i)
	{
		FAssetData& AssetData = AssetDatas[i];

		UDBItem* DBItem = Cast<UDBItem>(AssetData.GetAsset());

		if (DBItem != nullptr)
		{
			UDB* IsDB = Cast<UDB>(DBItem);

			if (IsDB != nullptr) {
				DB = IsDB;
			}

			Items.Add(DBItem);

			UE_LOG(LogTemp, Warning, TEXT("%d asset : %s"), i, *DBItem->GetName());
		}
	}

	DB->Items = Items;

	UE_LOG(LogTemp, Warning, TEXT("assets : %d"), AssetDatas.Num());

	return FReply::Handled();
}

void FDBPluginModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FDBPluginCommands::Get().OpenPluginWindow);
}

void FDBPluginModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FDBPluginCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDBPluginModule, DBPlugin)