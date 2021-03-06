// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Interactable.h"


// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 50.f;
	MovementSpeed = 0.3f;
	MovementBonusSpeed = 0.5f;
	LastMoveDirectrion = EMovementDirectrion::DOWN;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed);
	AddSnakeElement(1);
	
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ASnakeBase::AddSnakeElement(int ElementsNum)
{
	for (int i = 0; i < ElementsNum; ++i)
	{
		FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 0);
		FTransform NewTransform(NewLocation);
		ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
		NewSnakeElem->SnakeOwner = this;
		int32 ElemIndex = SnakeElements.Add(NewSnakeElem);
		
		if (ElemIndex == 0)
		{
			NewSnakeElem->SetFirtsElementType();
		}
	}
	
}

void ASnakeBase::Move()
{
	FVector MovementVector(ForceInitToZero);

	switch (LastMoveDirectrion)
	{
	case EMovementDirectrion::UP:
		MovementVector.X += ElementSize;
		break;
	case EMovementDirectrion::DOWN:
		MovementVector.X -= ElementSize;
		break;
	case EMovementDirectrion::LEFT:
		MovementVector.Y += ElementSize;
		break;
	case EMovementDirectrion::RIGHT:
		MovementVector.Y -= ElementSize;
		break;
	}

	/*AddActorWorldOffset(MovementVector);*/
	SnakeElements[0]->ToggleCollision();
	
	for (int i = SnakeElements.Num() - 1; i > 0; i--)
	{
		auto CurrentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];
		FVector PrevLocation = PrevElement->GetActorLocation();
		FVector LocalKostul(PrevLocation.X, PrevLocation.Y, 0);
		CurrentElement->SetActorLocation(LocalKostul);
	}
	for (int i = SnakeElements.Num() - 1; i > 0; i--)
	{
		SnakeElements[i]->ToggleVisible();   
	}

	FVector Kostul(MovementVector.X, MovementVector.Y, 5);    
	if (HeadUp == true)
	{
		SnakeElements[0]->AddActorWorldOffset(Kostul);
		SnakeElements[0]->ToggleCollision();
		HeadUp = false;
	}
	else
	{
		SnakeElements[0]->AddActorWorldOffset(MovementVector);
		SnakeElements[0]->ToggleCollision();
	}
}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other)
{
	if(IsValid(OverlappedElement))
	{	
		int32 ElemIndex;
		SnakeElements.Find(OverlappedElement, ElemIndex);
		bool bIsFirst = ElemIndex == 0;
		IInteractable* InteractableInterface = Cast<IInteractable>(Other);
		if (InteractableInterface)
		{
			InteractableInterface->Interact(this, bIsFirst);
		}
	}
}

void ASnakeBase::DestroySnake()
{
	for (int i = SnakeElements.Num() - 1; i >= 0; i--)
	{
		SnakeElements[i]->Destroy();
	}
}
