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
	_currentHealth = maxHealth;
}

/// <summary>
/// Function allows for character to take damage
/// </summary>
/// <param name="DamageAmount"></param>
/// <param name="DamageEvent"></param>
/// <param name="EventInstigator"></param>
/// <param name="DamageCauser"></param>
/// <returns></returns>
float AMazeCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!_isDead)
	{
		// Subtract the incoming damage
		_currentHealth -= DamageAmount;

		UE_LOG(LogTemp, Log, TEXT("Player took %f damage. %f health remaining."), DamageAmount, _currentHealth);

		if (_currentHealth <= 0)
		{
			Die();
		}

		return DamageAmount;
	}
	else
	{
		return 0;
	}
}

/// <summary>
/// Removes all control from the player and activates game over state
/// </summary>
void AMazeCharacter::Die()
{
	_isDead = true;
	_moveSpeed = 0;
	_rotationSpeed = 0;
	_jumpForce = 0;

	GetMesh()->PlayAnimation(_deathAnim, false);

	// ToDo: Trigger game over state and prompt the player to restart the level
}

// Called every frame
void AMazeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check if the player character is falling
	if (!GetCharacterMovement()->IsFalling())
	{
		// Player character has landed on the ground
		_isJumping = false;
	}
}

// Called to bind functionality to input
void AMazeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveFB"), this, &AMazeCharacter::MoveFB);
	PlayerInputComponent->BindAxis(TEXT("MoveLR"), this, &AMazeCharacter::MoveLR);
	PlayerInputComponent->BindAxis(TEXT("RotateYaw"), this, &AMazeCharacter::RotateYaw);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AMazeCharacter::Jump);
}

/// <summary>
/// Forward and backwards movement
/// </summary>
/// <param name="value"></param>
void AMazeCharacter::MoveFB(float value)
{
	AddMovementInput(GetActorForwardVector(), value * _moveSpeed);
}

/// <summary>
/// Left and right strafe movement
/// </summary>
/// <param name="value"></param>
void AMazeCharacter::MoveLR(float value)
{
	AddMovementInput(-GetActorRightVector(), value * _moveSpeed);
}

/// <summary>
/// Rotational movement of yaw
/// </summary>
/// <param name="value"></param>
void AMazeCharacter::RotateYaw(float value)
{
	AddControllerYawInput(value * _rotationSpeed);
}

/// <summary>
/// Jumping movement
/// </summary>
void AMazeCharacter::Jump()
{
	if (!_isJumping)
	{
		_isJumping = true;
		LaunchCharacter(FVector(0.0f, 0.0f, _jumpForce), false, true);
	}
}

