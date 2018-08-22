// Fill out your copyright notice in the Description page of Project Settings.

#include "GUIList.h"
#include <functional>
#include "AssistUtils/Public/AssistMapUtils.h"
#include "AssistUtils/Public/AssistArrayUtils.h"

void UGUIList::SetItems(TArray<UObject*> NewItems)
{
	std::function<UObject*(UGUIListItem*)> ItemsKeySelector = [](UGUIListItem* GuiListItem) -> UObject* { return GuiListItem->GetItem(); };
	std::function<UGUIListItem*(UGUIListItem*)> ItemsValueSelector = [](UGUIListItem* GuiListItem) -> UGUIListItem* { return GuiListItem; };
	TMap<UObject*, UGUIListItem*> GuiItemsByItems = AssistMapUtils::ToMap(ActiveItems, ItemsKeySelector, ItemsValueSelector);

	TArray<UGUIListItem*> ToRemove;
	TArray<UObject*> ToAdding;
	TArray<UGUIListItem*> ToAddingListItems;

	for (UGUIListItem* ListItem : ActiveItems)
	{
		if (!NewItems.Contains(ListItem->GetItem()) || !ListItem->GetItem())
		{
			ToRemove.Add(ListItem);
		}
	}

	for (UGUIListItem* ListItem : ToRemove)
	{
		ListItem->RemoveFromParent();
		ActiveItems.Remove(ListItem);
		InactiveItems.Add(ListItem);
	}

	for (UObject* Item : NewItems)
	{
		if (!GuiItemsByItems.Contains(Item))
		{
			ToAdding.Add(Item);
		}
	}

	for (UObject* Item : ToAdding)
	{
		if (InactiveItems.Num() > 0)
		{
			UGUIListItem* ListItem = AssistArrayUtils::First(InactiveItems);
			InactiveItems.Remove(ListItem);
			ListItem->SetItem(Item);
			ActiveItems.Add(ListItem);
		}
	}

	for (UGUIListItem* ListItem : ActiveItems)
	{
		if (ToAdding.Contains(ListItem->GetItem()))
		{
			ToAdding.Remove(ListItem->GetItem());
		}
	}

	for (UObject* Item : ToAdding)
	{
		UGUIListItem* NewListItem = CreateWidget<UGUIListItem>(GetWorld()->GetFirstPlayerController(), ListItemClass);
		NewListItem->SetItem(Item);
		ActiveItems.Add(NewListItem);
	}

	for (UGUIListItem* ListItem : ActiveItems)
	{
		E_AddListItem(ListItem);
	}
}

void UGUIList::E_AddListItem_Implementation(UGUIListItem* ListItem)
{
}