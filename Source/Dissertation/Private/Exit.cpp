// Fill out your copyright notice in the Description page of Project Settings.


#include "Exit.h"
#include "DissertationGameMode.h"

// Sets default values
AExit::AExit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Front Collision Check"));
	Collision->SetupAttachment(RootComponent);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AExit::OnOverlap);

}

void AExit::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AIndividual* Individual = Cast<AIndividual>(OtherActor);

	if (Individual)
	{
		Individual->EndTime = FDateTime::Now();
		FTimespan TimeSpent = Individual->EndTime - Individual->StartTime;

		GEngine->AddOnScreenDebugMessage(167, 10.0f, FColor::MakeRandomColor(), TimeSpent.ToString());
		ADissertationGameMode* GameMode = Cast<ADissertationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode)
		{
			GameMode->IndividualReferences.AddUnique(Individual);
			GameMode->SaveData(Individual->GetName(), Individual->BuyingState, Individual->NumOfCollisions, Individual->ListSize, TimeSpent);
		}
		Individual->Destroy();
	}
}

// Called when the game starts or when spawned
void AExit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

