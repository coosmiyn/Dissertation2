// Fill out your copyright notice in the Description page of Project Settings.


#include "Worker.h"

// Sets default values
AWorker::AWorker()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FrontCollisionCheck = CreateDefaultSubobject<USphereComponent>(TEXT("Front Collision Check"));
	FrontCollisionCheck->SetupAttachment(RootComponent);

	SurroundingsCollisionCheck = CreateDefaultSubobject<USphereComponent>(TEXT("Surroundings Collision Checl"));
	SurroundingsCollisionCheck->SetupAttachment(RootComponent);

	FrontCollisionCheck->OnComponentBeginOverlap.AddDynamic(this, &AWorker::OnFrontalCollisionOverlap);
	FrontCollisionCheck->OnComponentEndOverlap.AddDynamic(this, &AWorker::OnFrontalCollisionEndOverlap);
}

// Called when the game starts or when spawned
void AWorker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWorker::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AWorker::OnFrontalCollisionOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AWorker::OnFrontalCollisionEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

