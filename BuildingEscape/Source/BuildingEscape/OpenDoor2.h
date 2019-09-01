// Copyright Bradley Gray 2018

#pragma once

#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor2.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor2 : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor2();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//void OpenDoor();
	//void CloseDoor();

private:
	//UPROPERTY(EditAnywhere)
	//float OpenAngle = 90.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	float TriggerMass = 30.f;

	//UPROPERTY(EditAnywhere)
	//float DoorCloseDelay = 0.75f;

	//float LastDoorOpenTime;

	//AActor *ActorThatOpens; //Remember Pawn Inherits from Actor
	AActor *Owner; //The owning door
	// Return toal mass in kg
	float GetTotalMassOfActorsOnPlate();
};
