// Fill out your copyright notice in the Description page of Project Settings.

#include "MySnakeActor.h"
#include "MyCameraPawn.h"
#include "MyCameraPawn.h"

float MinY = -1530.f; float MaxY = 1350.f;// - 1500
float MinX = -940.f; float MaxX = 1000.f;//- 800
// Sets default values
AMySnakeActor::AMySnakeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyRootComponent = CreateDefaultSubobject<USphereComponent>("Myroot");

	RootComponent = MyRootComponent;

	FVector Posa = GetActorLocation();

	MyRootComponent->SetRelativeLocation(Posa);

	CreateSnakeBody();
}

// Called when the game starts or when spawned
void AMySnakeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMySnakeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetVisibleChark();
	
	BuferTime += DeltaTime;
	if (BuferTime > StepDeley)
	{

		MoveSnake();
		BuferTime = 0;
	}
}

void AMySnakeActor::CreateSnakeBody()
{

	class  UStaticMesh* SnakeChankMesh;

	SnakeChankMesh = ConstructorHelpers::FObjectFinder< UStaticMesh > (TEXT("/Engine/BasicShapes/Sphere")).Object;
	
	class UMaterialInstance*BodyColor;

	BodyColor = ConstructorHelpers::FObjectFinderOptional<UMaterialInstance>(TEXT("MaterialInstanceConstant'/Game/SnakeContent/Materials/InstanceMaterials/M_Tech_Hex_Tile_Inst.M_Tech_Hex_Tile_Inst'")).Get();

	class UMaterialInstance*WormHead;

	WormHead = ConstructorHelpers::FObjectFinderOptional<UMaterialInstance>(TEXT("MaterialInstanceConstant'/Game/SnakeContent/Materials/InstanceMaterials/M_Tech_Hex_Tile_Pulse_Inst.M_Tech_Hex_Tile_Pulse_Inst'")).Get();

	FVector NextPoint = GetActorLocation();

	FName NameChank;

	FString TheString;

	for (int32 i = 0; i < SnakeSize; i++) {

		TheString = "Chanks" + FString::FromInt(i);

		NameChank = FName(*TheString);

		UPROPERTY(EditAnywhere)	 UStaticMeshComponent* BodyChank = CreateDefaultSubobject<UStaticMeshComponent>(NameChank);

		BodyChank->SetStaticMesh(SnakeChankMesh);

		BodyChank->SetRelativeLocation(NextPoint);

		SnakeBody.Add(BodyChank);

		NextPoint.X -= StepSnake;

		BodyChank->AttachTo(MyRootComponent);

		BodyChank->SetMaterial(0, BodyColor);

		if (i == 0) {
			BodyChank -> SetMaterial(0, WormHead);
		}
		else{
			BodyChank -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}

	}
	SetVisibleChark();
}

void AMySnakeActor::SetVisibleChark()
{
	for (int32 IndexShow = 0; IndexShow < SnakeBody.Num(); IndexShow++) {
		if (IndexShow < VisibleBodyChank)
		{
			SnakeBody[IndexShow]->SetVisibility(true, true);
		}
		else{
			SnakeBody[IndexShow]->SetVisibility(false, true);
		}
	}
}
void AMySnakeActor::MoveSnake()
{
	FVector Posa = GetActorLocation();
	if ((DirectionMoveSnake.X != 0) || (DirectionMoveSnake.Y != 0))
	{
		for (int Chank = SnakeBody.Num() - 1; Chank > 0; Chank--) {

			FVector V = SnakeBody[Chank - 1]->RelativeLocation;

			SnakeBody[Chank] -> SetRelativeLocation(V);

		}

		FVector StartPoint = SnakeBody[0] -> RelativeLocation;
		
		if (DirectionMoveSnake.X > 0){ StartPoint.X += StepSnake; }

		if (DirectionMoveSnake.X < 0){ StartPoint.X -= StepSnake; }

	    if (DirectionMoveSnake.Y > 0){ StartPoint.Y += StepSnake; }

		if (DirectionMoveSnake.Y < 0){ StartPoint.Y -= StepSnake; }

		

		if (StartPoint.Y > MaxY) { StartPoint.Y = MinY; }
		if (StartPoint.Y < MinY) { StartPoint.Y = MaxY; }

		if (StartPoint.X > MaxX) { StartPoint.X = MinX; }
		if (StartPoint.X < MinX) { StartPoint.X = MaxX; }
		
		
		SnakeBody[0]->SetRelativeLocation(StartPoint);
		
	
		
	}
}
void AMySnakeActor::HaveDamage()
{
	WhoPawn -> SnakeDestroy();
}
;

