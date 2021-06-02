// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemTolltip.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAM_052021_API UItemTolltip : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, Category = "Tooltip", meta = (ExposeOnSpawn = true))
		class UInventoryItemWidget* InventoryItemWidget;

};
