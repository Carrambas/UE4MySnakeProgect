

#include "MyAppleActor.h"
#include <MySnakeActor.h>


AMyAppleActor::AMyAppleActor()
{
 
	PrimaryActorTick.bCanEverTick = true;


	

	MyRootComponent = CreateDefaultSubobject<USphereComponent>("RootEat");

	RootComponent = MyRootComponent;

	SnakeEatMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Sphere")).Object;

	class UMaterialInstance* EatColor;

	EatColor = ConstructorHelpers::FObjectFinderOptional<UMaterialInstance>(TEXT("MaterialInstanceConstant'/Game/SnakeContent/Materials/InstanceMaterials/M_Metal_Gold_Inst.M_Metal_Gold_Inst'")).Get();

	FVector Size = FVector(0.7f, 0.7f, 0.7f);

	class UStaticMeshComponent* EatChank = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Eat"));

	EatChank->SetStaticMesh(SnakeEatMesh);

	EatChank->SetRelativeScale3D(Size);

	EatChank->SetRelativeLocation(FVector(0, 0, 0));

	EatChank->SetMaterial(0, EatColor);

	EatChank->AttachTo(MyRootComponent);

	EatChank->SetSimulatePhysics(true);


}


void AMyAppleActor::BeginPlay()
{
	Super::BeginPlay();
	
}


void AMyAppleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	BuferTime += DeltaTime;
	if (BuferTime > StepDeley) {
		Destroy(true, true);
	}
	CollectEat();
}

void AMyAppleActor::CollectEat()
{
	TArray<AActor*> CollectedActors;
	
	GetOverlappingActors(CollectedActors);

	for (int32 i = 0; i < CollectedActors.Num(); ++i)
	{
		AMySnakeActor* const Test = Cast<AMySnakeActor>(CollectedActors[i]);

		if (Test) {
			Test->VisibleBodyChank++;
			Test->score++;

			Destroy(true, true);

			break;
		}
	}
}

