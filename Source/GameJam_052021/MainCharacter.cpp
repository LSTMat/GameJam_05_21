// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"

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
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

	PlayerInputComponent->BindAction(TEXT("IncreaseSpeed"), IE_Pressed, this, &AMainCharacter::IncreaseMovementSpeed);
	PlayerInputComponent->BindAction(TEXT("IncreaseSpeed"), IE_Released, this, &AMainCharacter::NormalizeMovementSpeed);
	PlayerInputComponent->BindAction(TEXT("DecreaseSpeed"), IE_Pressed, this, &AMainCharacter::DecreaseMovementSpeed);
	PlayerInputComponent->BindAction(TEXT("DecreaseSpeed"), IE_Released, this, &AMainCharacter::NormalizeMovementSpeed);
}

void AMainCharacter::MoveForeward(float AxisValue)
{
	if (AxisValue != 0.0f){
		AddMovementInput(GetActorForwardVector() * AxisValue);
		//UE_LOG(LogTemp, Warning, TEXT("FWD %f"), AxisValue);
	}
}

void AMainCharacter::MoveRight(float AxisValue)
{
	if (AxisValue != 0.0f){
		AddMovementInput(GetActorRightVector() * AxisValue);
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