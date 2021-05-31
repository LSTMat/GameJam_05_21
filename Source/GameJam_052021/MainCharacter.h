// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MainCharacter.generated.h"

USTRUCT()
struct FInteractionData
{

	GENERATED_BODY()

	FInteractionData()
	{
		ViewedInteractionComponent = nullptr;
		LastInteractionCheckTime = 0.f;
		bInteractHelf = false;
	}

	//Component for interaction
	UPROPERTY()
		class UInteractionComponent* ViewedInteractionComponent;

	//last time we check for an interactable
	UPROPERTY()
		float LastInteractionCheckTime;

	//if player is holding the action
	UPROPERTY()
		bool bInteractHelf;

};

class UCameraComponent;
UCLASS()
class GAMEJAM_052021_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Component for modify player speed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCharacterMovementComponent* PlayerCharacterMovement;

	//Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* CameraComponent;

	//if we are interacting with an item that has an interaction time
	bool IsInteracting() const;

	//get the time until we interact with the current interactable
	float GetRemainingInteractTime() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//How often we have to check if there is a interactable object in our range
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
		float InteractionCheckFrequency;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
		float InteractionCheckDistance;

	//check if there is an interactable object
	void PerformInteractionCheck();

	void CouldntFindInteractable();
	void FounddNewInteractable(UInteractionComponent* Interactable);

	//Start End Interaction checks
	void BeginInteract();
	void EndInteract();

	void Interact();

	//All the information for see the player interaction state
	UPROPERTY()
	FInteractionData InteractionData;

	//Helper function to make grabbing interactable faster
	FORCEINLINE class UInteractionComponent* GetInteractable() const {return InteractionData.ViewedInteractionComponent;}

	FTimerHandle TimerHandle_Interact;

private:

	//Sensibility for scrolling
	UPROPERTY(EditAnywhere)
		float VerticalRotationRate = 40;
	UPROPERTY(EditAnywhere)
		float HorizontalRotationRate = 40;

	//Values for different types of speed
	UPROPERTY(EditAnywhere)
		float SpeedRate = 1;
	UPROPERTY(EditAnywhere)
		float IncreasedSpeed = 800.0f;
	UPROPERTY(EditAnywhere)
		float NormalSpeed = 550.0f;
	UPROPERTY(EditAnywhere)
		float DecrasedSpeed = 300.0f;

	void MoveForeward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	//functions for modify speeds
	void IncreaseMovementSpeed();
	void NormalizeMovementSpeed();
	void DecreaseMovementSpeed();

};
