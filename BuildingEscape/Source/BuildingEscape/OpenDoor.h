// Copyright 2016 Jeff Largent

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
    void OpenDoor();
    void CloseDoor();
    
    UPROPERTY(BlueprintAssignable)
    FOnOpenRequest OnOpenRequest;

		
private:
    UPROPERTY(EditAnywhere)
    float OpenAngle = 160.0f;
    float CloseAngle = 90.0f;
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate = nullptr;
    float MassToOpenDoor = 30.f;
    
    UPROPERTY(EditAnywhere)
    float DoorClosedDelay = 0.5f;
    
    float LastDoorOpenTime;

    AActor* Owner = nullptr;
    
    // returns total mass in kg
    float GetTotalMassOfActorsOnPlate();
};
