// Copyright 2016 Jeff Largent

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


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

		
private:
    UPROPERTY(VisibleAnywhere)
    float OpenAngle = 180.0f;
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate;

    AActor* ActorThatOpens;
};
