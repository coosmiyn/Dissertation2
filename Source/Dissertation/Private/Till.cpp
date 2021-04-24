// Fill out your copyright notice in the Description page of Project Settings.


#include "Till.h"

// Sets default values
ATill::ATill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(StaticMesh);
	//StaticMesh->SetupAttachment(RootComponent);

	WorkerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Worker Capsule"));
	WorkerCapsule->SetupAttachment(RootComponent);

	ClientCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Client Capsule"));
	ClientCapsule->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ATill::GetClientTillCapsuleLocation() const
{
	return ClientCapsule->GetComponentLocation();
}

FVector ATill::GetWorkerTillCapsuleLocation() const
{
	return WorkerCapsule->GetComponentLocation();
}

