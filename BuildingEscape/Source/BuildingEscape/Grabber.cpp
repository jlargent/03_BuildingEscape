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
    
    /// look for attached PhysicsHandle
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandle)
    {
        // if PhysicsHandle is found
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("PhysicsHandle missing from: %s"), *GetOwner()->GetName());
    }
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	/// get player view point
    FVector PlayerViewPointLoacation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLoacation,
        OUT PlayerViewPointRotation);
    
    FVector LineTraceEnd = PlayerViewPointLoacation + PlayerViewPointRotation.Vector() * Reach;

    /// Draw a red trace in the world to visualise
    /*DrawDebugLine(GetWorld(),
                  PlayerViewPointLoacation,
                  LineTraceEnd,
                  FColor(255, 0, 0),
                  false,
                  0.f,
                  0.f,
                  10.f);
    */
    
    /// setup query parameters
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    
    /// line trace (AKA ray-cast) out to reach distance
    FHitResult Hit;
    GetWorld()->LineTraceSingleByObjectType(OUT Hit,
                                            PlayerViewPointLoacation,
                                            LineTraceEnd,
                                            FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                                            TraceParameters);
    
    /// see what we hit
    AActor* ActorHit = Hit.GetActor();
    if (ActorHit)
    {
        UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s."), *(ActorHit->GetName()));
    }
}

