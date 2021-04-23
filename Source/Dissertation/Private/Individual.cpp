// Fill out your copyright notice in the Description page of Project Settings.


#include "Individual.h"

// Sets default values
AIndividual::AIndividual()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FrontCollisionCheck = CreateDefaultSubobject<USphereComponent>(TEXT("Front Collision Check"));
	FrontCollisionCheck->SetupAttachment(RootComponent);

	SurroundingsCollisionCheck = CreateDefaultSubobject<USphereComponent>(TEXT("Surroundings Collision Checl"));
	SurroundingsCollisionCheck->SetupAttachment(RootComponent);

	FrontCollisionCheck->OnComponentBeginOverlap.AddDynamic(this, &AIndividual::OnFrontalCollisionOverlap);
	FrontCollisionCheck->OnComponentEndOverlap.AddDynamic(this, &AIndividual::OnFrontalCollisionEndOverlap);
}

// Called when the game starts or when spawned
void AIndividual::BeginPlay()
{
	Super::BeginPlay();
	
	GenerateShoppingList();

	for (int i = 0; i < ShoppingList.Num(); i++)
	{
		int id = FMath::RandRange(-100, 100);
		ADissertationGameMode* GameMode = Cast<ADissertationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode)
		{
			FString item = GameMode->EnumToString(TEXT("EAisleType"), static_cast<uint8>(ShoppingList[i]));
			GEngine->AddOnScreenDebugMessage(id, 3.0f, FColor::MakeRandomColor(), item);
		}
	}
}

// Called every frame
void AIndividual::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AIndividual::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AIndividual::OnFrontalCollisionOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AIndividual::OnFrontalCollisionEndOverlap(UPrimitiveComponent* OverlappedComp,	AActor* OtherActor,	UPrimitiveComponent* OtherComp,	int32 OtherBodyIndex)
{
}

void AIndividual::GenerateShoppingList()
{
	int listSize = FMath::RandRange(MinListSize, MaxListSize);

	for (int i = 0; i < listSize; i++)
	{
		int itemIndex = FMath::RandRange(0, static_cast<uint8>(EAisleType::MAX) - 1);
		ShoppingList.Add(static_cast<EAisleType>(itemIndex));
	}
}