// Copyright 2016 Jeff Largent

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"));

	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// get player view point
    FVector PlayerViewPointLoacation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLoacation,
        OUT PlayerViewPointRotation);
    
    // TODO: log out for testing
//    UE_LOG(LogTemp, Warning, TEXT("Location: %s Position: %s"),
//           *PlayerViewPointLoacation.ToString(),
//           *PlayerViewPointRotation.ToString());
//
    
    FVector LineTraceEnd = PlayerViewPointLoacation + PlayerViewPointRotation.Vector() * Reach;

    // Draw a red trace in the world to visualise
    DrawDebugLine(GetWorld(),
                  PlayerViewPointLoacation,
                  LineTraceEnd,
                  FColor(255, 0, 0),
                  false,
                  0.f,
                  0.f,
                  10.f);
    // ray-cast out to reach distance
    
    // see what we hit
}

