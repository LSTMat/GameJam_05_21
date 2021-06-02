// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom))
class GAMEJAM_052021_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Interaction")
		void UpdateInteractionWidget(class UInteractionComponent* InteractionComponent);

	UFUNCTION(BlueprintImplementableEvent)
		void OnUpdateInteractionWidget();

	UPROPERTY(BlueprintReadOnly, Category = "Interaction", meta = (ExposeOnSpawn))
		class UInteractionComponent* OwningInteractionComponent;
	
};
