// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonus.h"
#include "SnakeBase.h"

// Sets default values
ABonus::ABonus()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BonusSpeed = false;
	BonusPower = 1;
}

// Called when the game starts or when spawned
void ABonus::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABonus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABonus::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
		{
			Snake->AddSnakeElement(BonusPower);
			Destroy();
		}
		if (BonusSpeed == true)
		{
			Snake->SetActorTickInterval(Snake->MovementBonusSpeed += BonusPower);
			
		
		}
		Destroy();
	}

}

