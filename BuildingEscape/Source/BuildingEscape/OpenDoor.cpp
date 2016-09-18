// Copyright 2016 Jeff Largent

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
    Owner = GetOwner();
    if (!PressurePlate)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s missing PressurePlate"), *GetOwner()->GetName());
    }
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the Trigger Volume
    if(GetTotalMassOfActorsOnPlate() > MassToOpenDoor)
    {
        OpenDoor();
        LastDoorOpenTime = GetWorld()->GetTimeSeconds();
    }

    // Check if it's time to close the door
    if ((GetWorld()->GetTimeSeconds() - LastDoorOpenTime) > DoorClosedDelay)
    {
        CloseDoor();
    }
     
}

void UOpenDoor::OpenDoor()
{
    if(Owner == nullptr) { return; }
    Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
    if(Owner == nullptr) { return; }
    Owner->SetActorRotation(FRotator(0.0f, CloseAngle, 0.0f));
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
    float TotalMass = 0.f;
    
    // find all the overlapping actors
    TArray<AActor*>  OverlappingActors;
    if (!PressurePlate) { return TotalMass; }
    
    PressurePlate->GetOverlappingActors(OUT OverlappingActors);
    
    // iterate through them adding all their masses
    for(const auto& Actor : OverlappingActors)
    {
        TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    }
    
    return TotalMass;
}
