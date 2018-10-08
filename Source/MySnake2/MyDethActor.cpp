// Fill out your copyright notice in the Description page of Project Settings.

#include "MyDethActor.h"
#include <MySnakeActor.h>

// Sets default values
AMyDethActor::AMyDethActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	class UStaticMesh* WallMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Cube")).Object;

	WallColor = ConstructorHelpers::FObjectFinderOptional<UMaterialInstance>(TEXT("MaterialInstanceConstant'/Game/SnakeContent/Materials/InstanceMaterials/DangerMaterial_Inst.DangerMaterial_Inst'")).Get();

	MyRootComponent = CreateDefaultSubobject< UBoxComponent >("RootModel");

	RootComponent = MyRootComponent;

	class UStaticMeshComponent* WallChank;

	WallChank = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL"));

	WallChank->SetStaticMesh(WallMesh);

	WallChank->SetRelativeLocation(FVector(0, 0, 0));

	WallChank->SetMaterial(0, WallColor);

	WallChank->AttachTo(MyRootComponent);
}

// Called when the game starts or when spawned
void AMyDethActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyDethActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CollideWall();
}

void AMyDethActor::CollideWall()
{
	TArray<AActor*> CollectedActors;

	GetOverlappingActors(CollectedActors);

	for (int32 i = 0; i < CollectedActors.Num(); ++i)
	{
		AMySnakeActor* const Test = Cast<AMySnakeActor>(CollectedActors[i]);
		if (Test)
		{
			Test->HaveDamage();
		}
		else
		{
			CollectedActors[i]->Destroy(true, true);
		}
	}
}

