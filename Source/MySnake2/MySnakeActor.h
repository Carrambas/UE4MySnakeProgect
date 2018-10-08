#pragma once
#include <ConstructorHelpers.h>
#include "CoreMinimal.h"//
#include "GameFramework/Pawn.h"//
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"//
#include "Components/SphereComponent.h"//
#include "MySnakeActor.generated.h"//
UCLASS()
class MYSNAKE2_API AMySnakeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMySnakeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int32 SnakeSize = 150;
	float  StepSnake = 45.f;

	TArray<UStaticMeshComponent*>SnakeBody;

	UPROPERTY(EditAnywhere)	
 USphereComponent*MyRootComponent;

	void CreateSnakeBody();

	UPROPERTY(EditAnywhere)	int32 VisibleBodyChank = 5;

	void SetVisibleChark();

	UPROPERTY(EditAnywhere) FVector2D DirectionMoveSnake;

	float StepDeley = 0.05f;

	float BuferTime = 0;

	void MoveSnake();

	int32 score = 0;

	UPROPERTY(EditAnywhere) class  AMyCameraPawn* WhoPawn;

	void HaveDamage();
};
