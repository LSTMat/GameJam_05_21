// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#define LOCTEXT_NAMESPACE "Item"

UItem::UItem() 
{
    ItemDisplayName = LOCTEXT("ItemName", "Item");
}

bool UItem::ShouldShowInInventory() const
{
    return true;
}

#undef LOCTEXT_NAMEPSPACE