// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Core/Public/Containers/Queue.h"
#include "GUI.generated.h"

class UGUIFrame;
class UGUIFrameDBItem;
class UAssistGameInstance;

UCLASS()
class ASSISTCOREPLUGIN_API AGUI : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGUI();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAssistGameInstance* AssistGameInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<UGUIFrameDBItem*, UClass*> FramesClasses;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UGUIFrame* CurrentFrame;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UGUIFrameDBItem* CurrentFrameDBItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<UGUIFrameDBItem*, UGUIFrame*> FramesPool;

	TQueue<UGUIFrameDBItem*> FramesStack;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Show(UGUIFrameDBItem* FrameItem);

	void Back();
	
};
