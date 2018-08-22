// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AssistDBPlugin.h"
#include "AssistDBPluginStyle.h"
#include "AssistDBPluginCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "SButton.h"
#include "AssistDBPluginRuntime/Public/DBItem.h"
#include "AssistDBPluginRuntime/Public/DB.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

static const FName AssistDBPluginTabName("AssistDBPlugin");

#define LOCTEXT_NAMESPACE "FAssistDBPluginModule"

void FAssistDBPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FAssistDBPluginStyle::Initialize();
	FAssistDBPluginStyle::ReloadTextures();

	FAssistDBPluginCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FAssistDBPluginCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FAssistDBPluginModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FAssistDBPluginModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FAssistDBPluginModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(AssistDBPluginTabName, FOnSpawnTab::CreateRaw(this, &FAssistDBPluginModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FAssistDBPluginTabTitle", "AssistDBPlugin"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FAssistDBPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FAssistDBPluginStyle::Shutdown();

	FAssistDBPluginCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AssistDBPluginTabName);
}

TSharedRef<SDockTab> FAssistDBPluginModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
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
				.OnClicked_Raw(this, &FAssistDBPluginModule::CollectDB)
			]
		];
}

void FAssistDBPluginModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(AssistDBPluginTabName);
}

FReply FAssistDBPluginModule::CollectDB()
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

	if (DB == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("DB object not found in folder Game/DB"));
		return FReply::Handled();
	}

	UE_LOG(LogTemp, Warning, TEXT("DB path: %s ||| %s"), *DB->GetFName().ToString(), *DB->GetFullName());
	UPackage* Package = CreatePackage(NULL, TEXT("/Game/DB/DB"));
	Package->FullyLoad();

	DB->Items = Items;
	DB->SaveConfig();
	//UPackage::Save();
	Package->MarkPackageDirty();

	FString PackageFileName = FPackageName::LongPackageNameToFilename(TEXT("/Game/DB/DB"), FPackageName::GetAssetPackageExtension());
	bool bSaved = UPackage::SavePackage(Package, DB, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName, GError, nullptr, true, true, SAVE_NoError);

	UE_LOG(LogTemp, Warning, TEXT("assets : %d"), AssetDatas.Num());

	return FReply::Handled();
}

void FAssistDBPluginModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FAssistDBPluginCommands::Get().OpenPluginWindow);
}

void FAssistDBPluginModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FAssistDBPluginCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAssistDBPluginModule, AssistDBPlugin)