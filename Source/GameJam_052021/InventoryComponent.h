// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEJAM_052021_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	friend class UItem;

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UFUNCTION(BlueprintPure, Category = "Inventory")
		FORCEINLINE TArray<class UItem*> GetItems() const { return Items; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void AddItem(class UItem* Item);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
		TArray<class UItem*> Items;
		
};
