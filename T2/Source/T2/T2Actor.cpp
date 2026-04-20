// Fill out your copyright notice in the Description page of Project Settings.


#include "T2Actor.h"
#include "T2Object.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AT2Actor::AT2Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	SetRootComponent(Box);

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube'"));

	if (MeshRef.Succeeded())
	{
		Box->SetStaticMesh(MeshRef.Object);
	}

	Box->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AT2Actor::BeginPlay()
{
	Super::BeginPlay();

	T2Object = NewObject<UT2Object>();
	
	GEngine->ForceGarbageCollection(true);
}

// Called every frame
void AT2Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (T2Object == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Cyan, TEXT("Object Deleted"));
	}

	float Distance = DeltaTime * 50.0f;

	//FVector Location = GetActorLocation();
	//FVector NewLocation = Location + GetActorForwardVector() * Distance;
	//SetActorLocation(NewLocation);

	AddActorWorldOffset(GetActorForwardVector() * Distance);

	float RotationRate = 45.0f;
	//FRotator Rotation = GetActorRotation();
	//FRotator NewRotation = FRotator(Rotation.Pitch, Rotation.Yaw + RotationRate * DeltaTime, Rotation.Roll);

	//SetActorRotation(NewRotation);

	AddActorWorldRotation(FRotator(0.0f, RotationRate * DeltaTime, 0.0f));
}

