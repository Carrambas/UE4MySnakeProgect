// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "MyCameraPawn.generated.h"
UCLASS()
class MYSNAKE2_API AMyCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyCameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
	UPROPERTY(EditAnywhere)	
		UBoxComponent* MyRootComponent;

	UPROPERTY(EditAnywhere)	
		USpringArmComponent* CameraSpring;

	UPROPERTY(EditAnywhere) 
		UCameraComponent* MyCamera;

	class AMySnakeActor* MySnakePlayer;


	UFUNCTION(BlueprintCallable, Category =  "SnakePawn")

	void AddSnakeToMap();

	FVector2D WSAD;



	void FMove(float ButtonVal);
	
	float MinY = -1530.f; float MaxY =1350.f;// - 1500
	float MinX = -940.f; float MaxX = 1000.f;//- 800

	float SpawnZ = 50.f;

	void AddRandomApple();

	float StepDeley = 4.0f;
	float BuferTime = 0;

	int32 GameMode = 0;
	UFUNCTION(BlueprintCallable,Category = "SnakePawn")
	int32 GetGameMode() const { return GameMode; };

	UFUNCTION(BlueprintCallable, Category = "SnakePawn")

		int32 GetScore();

	bool GamePause = false;
	UFUNCTION(BlueprintCallable, Category = "SnakePawn")
		bool GetGamePause() const { return GamePause; };

	void SnakeDestroy();

};
