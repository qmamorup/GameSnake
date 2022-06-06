// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeBase.generated.h"

class ASnakeElementBase;

UENUM()
enum class EMovementDirectrion
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

UCLASS()
class GAMESNAKE_API ASnakeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeBase();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASnakeElementBase> SnakeElementClass;

	UPROPERTY(EditDefaultsOnly)
	float ElementSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementBonusSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Life;

	UPROPERTY()
	bool HeadUp;

	UPROPERTY()
	TArray<ASnakeElementBase*> SnakeElements;

	UPROPERTY()
	EMovementDirectrion LastMoveDirectrion;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void AddSnakeElement(int ElementsNum = 1);
	UFUNCTION(BlueprintCallable)
	void Move();
	UFUNCTION()
	void SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other);

	UFUNCTION(BlueprintCallable)
	void DestroySnake();

};
