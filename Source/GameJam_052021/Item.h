// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameJam_052021/MainCharacter.h"
#include "GameJam_052021/InventoryComponent.h"
#include "Item.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemModified);

/**
 * 
 */
UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class GAMEJAM_052021_API UItem : public UObject
{
	GENERATED_BODY()

	
public:

	UItem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		class UStaticMesh* PickupMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		class UTexture2D* Thumbail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText ItemDisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
		FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		TSubclassOf<class UItemTolltip> ItemTolltip;

	UPROPERTY()
		class UInventoryComponent* OwningInventory;

	UFUNCTION(BlueprintPure, Category = "Item")
		virtual bool ShouldShowInInventory() const;

	UPROPERTY(BlueprintAssignable)
		FOnItemModified OnItemModified;

	//virtual void Use(class AMainCharacter* Character);
	//virtual void AddedToInventory(class UInventoryComponent* Inventory);
};