// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyAppleActor.generated.h"

UCLASS()
class MYSNAKE2_API AMyAppleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyAppleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class USphereComponent* MyRootComponent;

	class UStaticMesh* SnakeEatMesh;
	
	void CollectEat();
	float StepDeley = 4.0f;

	float BuferTime = 0;
};
