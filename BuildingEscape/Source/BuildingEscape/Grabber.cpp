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
}

void UGrabber::Grab()
{
    UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
    
    /// line trace and see if we reach any actors with physics body collision channel set
    GetFirstPhysicsBodyInReach();
    
    /// if we hit something attach a physics handle
    // TODO: attach physics handle
}

void UGrabber::Release()
{
    UE_LOG(LogTemp, Warning, TEXT("Grab released"));
    // TODO: release physics handle
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
    FindPhysicsHandleComponent();
    SetupInputComponent();
}

// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
    
    /// if the physics handle is attached
        /// move the object that we are holding
}

void UGrabber::FindPhysicsHandleComponent()
{
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

void UGrabber::SetupInputComponent()
{
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent)
    {
        // found InputComponent
        UE_LOG(LogTemp, Warning, TEXT("InputComponent found"));
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("InputComponent missing from: %s"), *GetOwner()->GetName());
    }
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
   	/// get player view point
    FVector PlayerViewPointLoacation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
                                                               OUT PlayerViewPointLoacation,
                                                               OUT PlayerViewPointRotation);
    
    FVector LineTraceEnd = PlayerViewPointLoacation + PlayerViewPointRotation.Vector() * Reach;
    
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
    return FHitResult();
 
}