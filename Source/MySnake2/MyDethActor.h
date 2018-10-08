#pragma once
#include <ConstructorHelpers.h>
#include "LandscapeMaterialInstanceConstant.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h" 
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "MyDethActor.generated.h"
UCLASS()
class MYSNAKE2_API AMyDethActor : public AActor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AMyDethActor();


virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)    UBoxComponent* MyRootComponent;
	UPROPERTY(EditAnywhere)    UMaterialInstance* WallColor;
	
	void CollideWall();
};
