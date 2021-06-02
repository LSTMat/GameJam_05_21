// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StaticMeshComponent.h"
#include "GameJam_052021/Item.h"
#include "GameJam_052021/InteractionComponent.h"
#include "Pickup.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	PickupMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

    SetRootComponent(RootComponent);

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComponent");
	InteractionComponent->InteractionTime = 0.5f;
	InteractionComponent->InteractionDistance = 200.f;
	InteractionComponent->InteractionObjectName = FText::FromString("Pickup");
	InteractionComponent->InteractionObjectAction = FText::FromString("Take");
	InteractionComponent->SetupAttachment(PickupMesh);

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
	if(Item)
	{
		PickupMesh->SetStaticMesh(Item->PickupMesh);
	}

}

