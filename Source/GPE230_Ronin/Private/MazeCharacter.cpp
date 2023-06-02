// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMazeCharacter::AMazeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMazeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMazeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check if the player character is falling
	if (!GetCharacterMovement()->IsFalling())
	{
		// Player character has landed on the ground
		isJumping = false;
	}
}

// Called to bind functionality to input
void AMazeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveFB"), this, &AMazeCharacter::MoveFB);
	PlayerInputComponent->BindAxis(TEXT("MoveLR"), this, &AMazeCharacter::MoveLR);
	PlayerInputComponent->BindAxis(TEXT("Rotate"), this, &AMazeCharacter::Rotate);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AMazeCharacter::Jump);
}

/// <summary>
/// Forward and backwards movement
/// </summary>
/// <param name="value"></param>
void AMazeCharacter::MoveFB(float value)
{
	AddMovementInput(GetActorForwardVector(), value * moveSpeed);
}

/// <summary>
/// Left and right strafe movement
/// </summary>
/// <param name="value"></param>
void AMazeCharacter::MoveLR(float value)
{
	AddMovementInput(-GetActorRightVector(), value * moveSpeed);
}

/// <summary>
/// Rotational movement
/// </summary>
/// <param name="value"></param>
void AMazeCharacter::Rotate(float value)
{
	AddControllerYawInput(value * rotationSpeed);
}

/// <summary>
/// Jumping movement
/// </summary>
void AMazeCharacter::Jump()
{
	if (!isJumping)
	{
		isJumping = true;
		LaunchCharacter(FVector(0.0f, 0.0f, jumpForce), false, true);
	}
}

