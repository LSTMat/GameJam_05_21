// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabberComponent.h"

// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();

	SetUpInputComponent();

}


void UGrabberComponent::SetUpInputComponent() 
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabberComponent::Grab);
	}
}

void UGrabberComponent::Grab() 
{

	UE_LOG(LogTemp, Warning, TEXT("Grab"));
	FHitResult Hit = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = Hit.GetComponent();


	if (Hit.GetActor()) {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Hit.GetActor()->GetName());

		Hit.GetActor()->SetActorHiddenInGame(true);
		Hit.GetActor()->SetActorEnableCollision(false);

	}

}


// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	//UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *PlayerViewPointRotation.Vector().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Rotation: %s"), *PlayerViewPointRotation.ToString());

}

FHitResult UGrabberComponent::GetFirstPhysicsBodyInReach() const
{
	//DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(0, 255, 0), false, 0.f, 0, 5.f);

	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(OUT Hit, GetPlayerWorldPos(), GetPlayerReach(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);

	AActor* HitComponent = Hit.GetActor();

	if (HitComponent != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit with: %s"), *Hit.GetActor()->GetName());
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("no"));
	}

	return Hit;
}

FVector UGrabberComponent::GetPlayerReach() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);

}

FVector UGrabberComponent::GetPlayerWorldPos() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return PlayerViewPointLocation;
}