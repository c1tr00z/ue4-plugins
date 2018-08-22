// Fill out your copyright notice in the Description page of Project Settings.

#include "GUIListItem.h"
#include "GUI/List/GUIList.h"

void UGUIListItem::SetItem(UObject * NewItem)
{
	Item = NewItem;
}

UObject * UGUIListItem::GetItem()
{
	return Item;
}
