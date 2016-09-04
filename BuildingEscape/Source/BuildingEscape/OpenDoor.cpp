// Copyright 2016 Jeff Largent

#include "BuildingEscape.h"
#include "OpenDoor.h"


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
    
   ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the Trigger Volume
    // If the ActorThatOpens in in the volume
    if(PressurePlate->IsOverlappingActor(ActorThatOpens))
    {
        OpenDoor();
    }
}

void UOpenDoor::OpenDoor()
{
    AActor* Owner = GetOwner();
    
    FRotator NewRotation = FRotator(0.0f, 180.0f, 0.0f);
    Owner->SetActorRotation(NewRotation);
}