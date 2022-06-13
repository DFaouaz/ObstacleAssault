// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// cache intial location
	initialLocation = GetActorLocation();

	FString name = GetName();											 // gets name of the actor
	UE_LOG(LogTemp, Display, TEXT("%s: On Begin Play Executed"), *name); // * operator returns a c++ string aka char*
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	// SetActorLocation(FVector) to set actors' position
	// GetActorLocation() to get actors' position
	FVector location = GetActorLocation();
	location += velocity * DeltaTime;

	double distance = FVector::Distance(location, initialLocation);
	if (ShouldPlatformReturn())
	{
		// Get normalize vector | Use v.Normalize() to normalize v vector
		FVector direction = velocity.GetSafeNormal();
		// if (direction.IsZero())	throw new Exception();
		location = initialLocation + direction * (2.0 * maxDistance - distance); // set location with offset

		// fake initial location and swap velocity direction
		initialLocation = initialLocation + direction * maxDistance;
		velocity *= -1;
	}

	SetActorLocation(location);
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	// SetActorLocation(FVector) to set actors' position
	// GetActorLocation() to get actors' position
	FRotator rotation = GetActorRotation();
	rotation += rotationVelocity * DeltaTime;
	SetActorRotation(rotation);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() >= maxDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Distance(GetActorLocation(), initialLocation);
}

