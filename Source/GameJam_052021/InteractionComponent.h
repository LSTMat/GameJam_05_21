// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "InteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginInteract, class AMainCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndInteract, class AMainCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginFocus, class AMainCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndFocus, class AMainCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, class AMainCharacter*, Character);

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAMEJAM_052021_API UInteractionComponent : public UWidgetComponent
{
	GENERATED_BODY()

public :
	UInteractionComponent();

	//How much time is needed to take the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	float InteractionTime;

	//From how far the player can interact with the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")
	float InteractionDistance;

	//Name of the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")
	FText InteractionObjectName;

	//Action of the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")
	FText InteractionObjectAction;

	UFUNCTION(BluePrintCallable, Category = "Interaction")
		void SetInteractableNameText(const FText& NewNameText);

	UFUNCTION(BluePrintCallable, Category = "Interaction")
		void SetInteractableActionText(const FText& NewActionText);

	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnBeginInteract OnBeginInteract;

	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnEndInteract OnEndInteract;

	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnBeginFocus OnBeginFocus;

	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnEndFocus OnEndFocus;

	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnInteract OnInteract;

	//called when the player trace hit the object
	void BeginFocus(class AMainCharacter* Character);
	void EndFocus(class AMainCharacter* Character);

	//called when the player start/end to interact with the object
	void BeginInteract(class AMainCharacter* Character);
	void EndInteract(class AMainCharacter* Character);

	void Interact(class AMainCharacter* Character);

	//how far we are to complete the interaction, will return a value from 0 to 1
	UFUNCTION(BlueprintPure, Category = "Interaction")
	float GetInteractPercentage();

	void RefreshWidget();

	class AMainCharacter* Interactor = nullptr;

protected:
	virtual void Deactivate();

};
