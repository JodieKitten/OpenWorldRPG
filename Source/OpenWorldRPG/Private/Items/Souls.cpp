// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Souls.h"
#include "Interfaces/PickupInterface.h"


void ASouls::BeginPlay()
{
	Super::BeginPlay();
}

void ASouls::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*const double LocationZ = GetActorLocation().Z;
	if (LocationZ > DesiredZ)
	{
		const FVector DeltaLocation = FVector(0.f, 0.f, DriftRate * DeltaTime);
		AddActorWorldOffset(DeltaLocation);
	}*/
}

void ASouls::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	if (PickupInterface)
	{
		PickupInterface->AddSouls(this);
		SpawnPickupSystem();
		SpawnPickupSound();
		Destroy();
	}
}
