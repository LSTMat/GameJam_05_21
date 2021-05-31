// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameJam_052021/InteractionComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacterMovement = GetCharacterMovement();

	InteractionCheckFrequency  = 0.f;
	InteractionCheckDistance = 1000.f;
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PerformInteractionCheck();

}

void AMainCharacter::PerformInteractionCheck() 
{

	if(GetController() == nullptr){
		return;
	}

	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();

	FVector EyesLoc;
	FRotator EyesRot;

	GetController()->GetPlayerViewPoint(EyesLoc, EyesRot);

	FVector TraceStart = EyesLoc;
	FVector TraceEnd = (EyesRot.Vector() * InteractionCheckDistance) + TraceStart;
	FHitResult TraceHit;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{
		if(TraceHit.GetActor())
		{
			if(UInteractionComponent* InteractionComponent = Cast<UInteractionComponent>(TraceHit.GetActor()->GetComponentByClass(UInteractionComponent::StaticClass())))
			{
				float Distance = (TraceStart - TraceHit.ImpactPoint).Size();

				if(InteractionComponent != GetInteractable() && Distance <= InteractionComponent->InteractionDistance)
				{
					FounddNewInteractable(InteractionComponent);
				}
				else if (Distance > InteractionComponent->InteractionDistance && GetInteractable())
				{
					CouldntFindInteractable();
				}

				return;

			}
		}
	}

	CouldntFindInteractable();

}

void AMainCharacter::CouldntFindInteractable() 
{
	if (GetWorldTimerManager().IsTimerActive(TimerHandle_Interact))
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Interact);
	}

	if(UInteractionComponent* Interactable = GetInteractable())
	{
		Interactable->EndFocus(this);

		if (InteractionData.bInteractHelf)
		{
			EndInteract();
		}
	}

	InteractionData.ViewedInteractionComponent = nullptr;
}

void AMainCharacter::FounddNewInteractable(UInteractionComponent* Interactable) 
{
	EndInteract();

	if(UInteractionComponent* OldInteractable = GetInteractable())
	{
		OldInteractable->EndFocus(this);
	}

	InteractionData.ViewedInteractionComponent = Interactable;
	Interactable->BeginFocus(this);
}

void AMainCharacter::BeginInteract() 
{
	InteractionData.bInteractHelf = true;

	if (UInteractionComponent* Interactable = GetInteractable())
	{
		Interactable->BeginInteract(this);
		
		if (FMath::IsNearlyZero(Interactable->InteractionTime))
		{
			Interact();
		}
		else
		{
			GetWorldTimerManager().SetTimer(TimerHandle_Interact, this, &AMainCharacter::Interact, Interactable->InteractionTime, false);
		}
	}
}

void AMainCharacter::EndInteract() 
{
	InteractionData.bInteractHelf = false;

	GetWorldTimerManager().ClearTimer(TimerHandle_Interact);

	if (UInteractionComponent* Interactable = GetInteractable())
	{
		Interactable->EndInteract(this);
	}
}

void AMainCharacter::Interact() 
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interact);

	if(UInteractionComponent* Interactable = GetInteractable())
	{
		Interactable->Interact(this);
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Setting up all the movement and main key for the character (PC/Joypad)
	PlayerInputComponent->BindAxis(TEXT("MoveForeward"), this, &AMainCharacter::MoveForeward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMainCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AMainCharacter::LookRightRate);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AMainCharacter::LookUpRate);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &AMainCharacter::BeginInteract);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Released, this, &AMainCharacter::EndInteract);

	PlayerInputComponent->BindAction(TEXT("IncreaseSpeed"), IE_Pressed, this, &AMainCharacter::IncreaseMovementSpeed);
	PlayerInputComponent->BindAction(TEXT("IncreaseSpeed"), IE_Released, this, &AMainCharacter::NormalizeMovementSpeed);
	PlayerInputComponent->BindAction(TEXT("DecreaseSpeed"), IE_Pressed, this, &AMainCharacter::DecreaseMovementSpeed);
	PlayerInputComponent->BindAction(TEXT("DecreaseSpeed"), IE_Released, this, &AMainCharacter::NormalizeMovementSpeed);
}

bool AMainCharacter::IsInteracting() const
{
	return GetWorldTimerManager().IsTimerActive(TimerHandle_Interact);
}

float AMainCharacter::GetRemainingInteractTime() const
{
	return GetWorldTimerManager().GetTimerRemaining(TimerHandle_Interact);
}

void AMainCharacter::MoveForeward(float AxisValue)
{
	if (AxisValue != 0.0f){
		AddMovementInput(GetActorForwardVector() * AxisValue);
		NormalizeMovementSpeed();
		//UE_LOG(LogTemp, Warning, TEXT("FWD %f"), AxisValue);
	}
}

void AMainCharacter::MoveRight(float AxisValue)
{
	if (AxisValue != 0.0f){
		AddMovementInput(GetActorRightVector() * AxisValue);
		NormalizeMovementSpeed();
		//UE_LOG(LogTemp, Warning, TEXT("RIGHT %f"), AxisValue);
	}
}

void AMainCharacter::IncreaseMovementSpeed() 
{
	PlayerCharacterMovement->MaxWalkSpeed = IncreasedSpeed * SpeedRate;
}

void AMainCharacter::NormalizeMovementSpeed() 
{
	PlayerCharacterMovement->MaxWalkSpeed = NormalSpeed * SpeedRate;
}

void AMainCharacter::DecreaseMovementSpeed()
{
	PlayerCharacterMovement->MaxWalkSpeed = DecrasedSpeed * SpeedRate;
}

void AMainCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * VerticalRotationRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * HorizontalRotationRate * GetWorld()->GetDeltaSeconds());
}