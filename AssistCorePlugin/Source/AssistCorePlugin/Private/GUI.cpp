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
		static ConstructorHelpers::FClassFinder<UGUIFrame> mainMenuWidgetClassFinder(*FrameItem->GetWidgetClassPath());
		if (mainMenuWidgetClassFinder.Succeeded())
		{
			FramesClasses.Add(FrameItem, (UClass*)mainMenuWidgetClassFinder.Class);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("GUI Created"));
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
	if (AssistGameInstance == nullptr || AssistGameInstance == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Game instance not initialized yet"));
		return;
	}

	if (CurrentFrameDBItem == FrameItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("Frame %s already showed"), *FrameItem->GetName());
		return;
	}

	if (!FramesClasses.Contains(FrameItem))
	{
		UE_LOG(LogTemp, Error, TEXT("Frame %s not preloaded"), *FrameItem->GetName());
		return;
	}

	if (CurrentFrame != nullptr && CurrentFrame != NULL)
	{
		CurrentFrame->RemoveFromParent();
	}

	if (FramesPool.Contains(FrameItem))
	{
		UE_LOG(LogTemp, Warning, TEXT("Frame %s already created"), *FrameItem->GetName());
		CurrentFrame = FramesPool[FrameItem];
	}
	else
	{
		CurrentFrame = CreateWidget<UGUIFrame>(AssistGameInstance, FramesClasses[FrameItem]);
		CurrentFrameDBItem = FrameItem;
		UE_LOG(LogTemp, Log, TEXT("Frame %s created"), *CurrentFrame->GetName());
	}

	if (FrameItem->StackIt)
	{
		FramesStack.Enqueue(FrameItem);
	}

	CurrentFrame->AddToViewport();
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

