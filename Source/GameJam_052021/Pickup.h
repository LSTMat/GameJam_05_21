// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class GAMEJAM_052021_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", Instanced)
		class UItem* Item;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    	class UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
		class UInteractionComponent* InteractionComponent;

};
