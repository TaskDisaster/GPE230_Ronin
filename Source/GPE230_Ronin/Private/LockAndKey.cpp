// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeCharacter.h"
#include "LockAndKey.h"

ALockAndKey::ALockAndKey()
{
	OnActorBeginOverlap.AddDynamic(this, &ALockAndKey::CheckActorType);
}

/// <summary>
/// Check if the other actor in this trigger is a MazeCharacter. If it is, open the door.
/// </summary>
/// <param name="OverlappedActor"></param>
/// <param name="OtherActor"></param>
void ALockAndKey::CheckActorType(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->IsA(AMazeCharacter::StaticClass()))
		OpenTheDoor();
}

/// <summary>
/// Opens the door
/// </summary>
void ALockAndKey::OpenTheDoor()
{
	this->Destroy();
}
