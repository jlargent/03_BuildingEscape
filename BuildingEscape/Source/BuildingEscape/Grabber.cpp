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
    
    if (!PhysicsHandle) { return; }
    /// if the physics handle is attached
    if (PhysicsHandle->GrabbedComponent)
    {
        /// move the object that we are holding
        PhysicsHandle->SetTargetLocation(GetReachLineEnd());
    }
}

void UGrabber::FindPhysicsHandleComponent()
{
    /// look for attached PhysicsHandle
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandle == nullptr)
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

void UGrabber::Grab()
{
    // line trace and see if we reach any actors with physics body collision channel set
    auto HitResult = GetFirstPhysicsBodyInReach();
    auto ComponentToGrab = HitResult.GetComponent();
    auto ActorHit = HitResult.GetActor();
    
    // if we hit something attach a physics handle
    if (ActorHit)
    {
        if(!PhysicsHandle) { return; }
        PhysicsHandle->GrabComponent(ComponentToGrab,
                                     NAME_None,
                                     ComponentToGrab->GetOwner()->GetActorLocation(),
                                     true);
    }
}

void UGrabber::Release()
{
    if(!PhysicsHandle) { return; }
    // release physics handle
    PhysicsHandle->ReleaseComponent();
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
    // setup query parameters
    
    /// line trace (AKA ray-cast) out to reach distance
    FHitResult HitResult;
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    GetWorld()->LineTraceSingleByObjectType(OUT HitResult ,
                                            GetReachLineStart(),
                                            GetReachLineEnd(),
                                            FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                                            TraceParameters
                                            );

    return HitResult;
}

FVector UGrabber::GetReachLineStart()
{
    FVector PlayerViewPointLoacation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLoacation,
                                                               OUT PlayerViewPointRotation);
    
    return PlayerViewPointLoacation;
}

FVector UGrabber::GetReachLineEnd()
{
    FVector PlayerViewPointLoacation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLoacation,
                                                               OUT PlayerViewPointRotation);
    
    return PlayerViewPointLoacation + PlayerViewPointRotation.Vector() * Reach;
}
