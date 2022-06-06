// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralRoom.h"
#include "DrawDebugHelpers.h"

// Sets default values
AProceduralRoom::AProceduralRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorComponent"));
	SetRootComponent(Floor);
}

// Called when the game starts or when spawned
void AProceduralRoom::BeginPlay()
{
	Super::BeginPlay();

	SpawnItem(Food);
	SpawnItem(Bonus);
	SpawnItem(Food);
	SpawnItem(Bonus);
	SpawnItem(Food);
	SpawnItem(Food);
	SpawnItem(Food);
	SpawnItem(Food);
	SpawnItem(Food);
	SpawnItem(Food);
	SpawnItem(Food);
	SpawnItem(Food);
	SpawnItem(Food);
	SpawnItem(Food);
	SpawnItem(Food);
	SpawnItem(Food);
}

// Called every frame
void AProceduralRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AProceduralRoom::SpawnItem(UClass* ItemToSpawn)
{
	float XCoordinate = FMath::FRandRange(-500.f, 500.f);
	float YCoordinate = FMath::FRandRange(-500.f, 500.f);
	
	float Yaw = FMath::FRandRange(0.f, 0.f);

	FVector Location(XCoordinate, YCoordinate, 0.f);
	FRotator Rotation(0.f, Yaw, 0.f);
	
	GetWorld()->SpawnActor<AActor>(ItemToSpawn, Location, Rotation);
}

