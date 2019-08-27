// Copyright Bradley Gray 2018

#include "OpenDoor2.h"
#include "BuildingEscape.h"
#define OUT
// Sets default values for this component's properties
UOpenDoor2::UOpenDoor2()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor2::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	if (Owner == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT(" Owner is null: "));
	}

	//ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor2::OpenDoor()
{
	//Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
	UE_LOG(LogTemp, Error, TEXT(" Open Door "));

	OnOpenRequest.Broadcast();
}

void UOpenDoor2::CloseDoor()
{
	if (!Owner)
	{
		return;
	}
	Owner->SetActorRotation(FRotator(0.f, 90.f, 0.f));
}


// Called every frame
void UOpenDoor2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll the trigger volume
	//If the ActorThatOpens is in the volume
	if (GetTotalMassOfActorsOnPlate() > 50.f) // TODO make into a parameter
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	//Check if it's time to close the door
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}

}
float UOpenDoor2::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	// Find all the overlapping actors
	TArray<AActor*> OverlappingActors;

	if (!PressurePlate)
	{
		if (!Owner)
		{
			return -1.f;
		}
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *GetOwner()->GetName());
		return -1.f;
	}
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	// Iterate through them adding their masses
	for (const auto& Actor : OverlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor Name: %s"), *(Actor->GetName()));
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}