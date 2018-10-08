// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCameraPawn.h"
#include "MySnakeActor.h"
#include "MyAppleActor.h"
// Sets default values
AMyCameraPawn::AMyCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyRootComponent = CreateDefaultSubobject<UBoxComponent>("RootModel");

	RootComponent = MyRootComponent;


	CameraSpring = CreateDefaultSubobject<USpringArmComponent>("Spring");

	CameraSpring->SetRelativeLocation(FVector(0, 0, 0));

	CameraSpring->AttachTo(MyRootComponent);

	MyCamera = CreateDefaultSubobject <UCameraComponent>("camera");

	MyCamera->AttachTo(CameraSpring, USpringArmComponent::SocketName);

	CameraSpring-> SetRelativeRotation(FRotator(-90.f, 0, 0));

	CameraSpring-> TargetArmLength = 1900.f;
	CameraSpring-> bDoCollisionTest = false;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void AMyCameraPawn::BeginPlay()
{
	Super::BeginPlay();


	

}

// Called every frame
void AMyCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GameMode > 0) {
		BuferTime += DeltaTime;
		if (BuferTime > StepDeley) {

			if (!GamePause)	AddRandomApple();
			BuferTime = 0;
		}
	}
}

// Called to bind functionality to input
void AMyCameraPawn::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("KeyMapMove", this, &AMyCameraPawn::FMove);
}

void AMyCameraPawn::AddSnakeToMap()
{
	// получение позиции стартовой точки
	FVector StartPoint = GetActorLocation();
	// получение поворота пешки
	FRotator StartPointRotation = GetActorRotation();

	//проверка на наличие сцены и если да то ставим актёра в точку 
	if (GetWorld())
	{
		MySnakePlayer = GetWorld()->SpawnActor<AMySnakeActor>(StartPoint, StartPointRotation);

		GameMode = 1;
		MySnakePlayer -> WhoPawn = this;
	}
}

void AMyCameraPawn::FMove(float ButtonVal)
{



	int32 Key = ButtonVal;
	if (GameMode > 0) {
		if (Key == 5) {

			GamePause = !GamePause;

		}
		if (!GamePause) {
			switch (Key) {
			case 1:
				if (WSAD.X != -1) {
					WSAD = FVector2D(0, 0);
					WSAD.X = 1;
				}
				break;

			case 2:
				if (WSAD.X != 1) {
					WSAD = FVector2D(0, 0);
					WSAD.X = -1;
				}
				break;

			case 3:
				if (WSAD.Y != -1) {
					WSAD = FVector2D(0, 0);
					WSAD.Y = 1;
				}
				break;

			case 4:
				if (WSAD.Y != 1) {
					WSAD = FVector2D(0, 0);
					WSAD.Y = -1;
				}
				break;
			}

			if (MySnakePlayer) {
				MySnakePlayer->DirectionMoveSnake = WSAD;
			}

		}
		else { MySnakePlayer->DirectionMoveSnake = FVector2D(0, 0); }
	}
}

void AMyCameraPawn::AddRandomApple()
{
	FRotator StartPointRotation = FRotator(0, 0, 0);

	float SpawnX = FMath::FRandRange(MinX, MaxX);
	float SpawnY = FMath::FRandRange(MinY, MaxY);

	FVector StartPoint = FVector(SpawnX, SpawnY, SpawnZ);

	if (MySnakePlayer)
	{
		if (GetWorld())
		{
			GetWorld()->SpawnActor<AMyAppleActor>(StartPoint, StartPointRotation);
		}
	}
}

int32 AMyCameraPawn::GetScore()
{
	if (MySnakePlayer)
	{
		return MySnakePlayer->score;
	}
	return 0;
	return int32();
}

void AMyCameraPawn::SnakeDestroy()
{
	GameMode = 0;

	if (MySnakePlayer) MySnakePlayer->Destroy(true, true);
}

