// Fill out your copyright notice in the Description page of Project Settings.


#include "Aisle.h"

// Sets default values
AAisle::AAisle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AAisle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAisle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

