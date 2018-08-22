// Fill out your copyright notice in the Description page of Project Settings.

#include "GUI.h"
#include "GUI/GUIFrame.h"
#include "GUI/GUIFrameDBItem.h" 
#include "AssistGameInstance.h"
#include "DBLoader.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"


// Sets default values
AGUI::AGUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TArray<UGUIFrameDBItem*> FramesItems = DBLoader::GetItems<UGUIFrameDBItem>();
	for (UGUIFrameDBItem* FrameItem : FramesItems)
	{
		DBLoader::LoadBPClass(FrameItem, FString(TEXT("Frame")));
		ConstructorHelpers::FClassFinder<UGUIFrame> mainMenuWidgetClassFinder(*FrameItem->GetWidgetClassPath());
		if (mainMenuWidgetClassFinder.Succeeded())
		{
			UE_LOG(LogTemp, Warning, TEXT("Class for frame %s preloaded [%s]"), *FrameItem->GetName(), *((UClass*)mainMenuWidgetClassFinder.Class)->GetFullName());
			FramesClasses.Add(FrameItem, (UClass*)mainMenuWidgetClassFinder.Class);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("GUI Created [%d frames classes preloaded]"), FramesClasses.Num());
}

// Called when the game starts or when spawned
void AGUI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGUI::Show(UGUIFrameDBItem * FrameItem)
{
	if (CurrentFrameDBItem == FrameItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("Frame %s already showed"), *FrameItem->GetName());
		return;
	}

	if (!FramesClasses.Contains(FrameItem) || FramesClasses[FrameItem] == nullptr || FramesClasses[FrameItem] == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Frame %s not preloaded"), *FrameItem->GetName());
		return;
	}

	
	E_Show(FrameItem, FramesClasses[FrameItem]);
}

void AGUI::E_Show_Implementation(UGUIFrameDBItem* FrameItem, TSubclassOf<UGUIFrame> FrameClass)
{
}

void AGUI::Back()
{
	UGUIFrameDBItem* BackFrameDBItem = nullptr;

	while (BackFrameDBItem == nullptr || BackFrameDBItem == CurrentFrameDBItem)
	{
		FramesStack.Dequeue(BackFrameDBItem);
	}

	Show(BackFrameDBItem);
}

