// Fill out your copyright notice in the Description page of Project Settings.


#include "Individual.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "DissertatioNGameMode.h"

// Sets default values
AIndividual::AIndividual()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FrontCollisionCheck = CreateDefaultSubobject<USphereComponent>(TEXT("Front Collision Check"));
	FrontCollisionCheck->SetupAttachment(RootComponent);

	SurroundingsCollisionCheck = CreateDefaultSubobject<USphereComponent>(TEXT("Surroundings Collision Checl"));
	SurroundingsCollisionCheck->SetupAttachment(RootComponent);

	InLineCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("In Line Capsule"));
	InLineCapsule->SetupAttachment(RootComponent);

	FrontCollisionCheck->OnComponentBeginOverlap.AddDynamic(this, &AIndividual::OnFrontalCollisionOverlap);
	FrontCollisionCheck->OnComponentEndOverlap.AddDynamic(this, &AIndividual::OnFrontalCollisionEndOverlap);
}

// Called when the game starts or when spawned
void AIndividual::BeginPlay()
{
	Super::BeginPlay();
	
	StartTime = FDateTime::Now();
	GenerateShoppingList();

	for (int i = 0; i < ShoppingList.Num(); i++)
	{
		int id = FMath::RandRange(-100, 100);
		ADissertationGameMode* GameMode = Cast<ADissertationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode)
		{
			FString item = GameMode->EnumToString(TEXT("EAisleType"), static_cast<uint8>(ShoppingList[i]));
			//GEngine->AddOnScreenDebugMessage(id, 3.0f, FColor::MakeRandomColor(), item);
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
	UCapsuleComponent* Mesh2 = Cast<UCapsuleComponent>(OverlappedComp);
	UCapsuleComponent* Mesh3 = Cast<UCapsuleComponent>(OtherComp);
	//GEngine->AddOnScreenDebugMessage(1237, 100.0f, FColor::MakeRandomColor(), TEXT("OVERLAP OVERLAP OVERLAP OVERLAP "));

	if (Mesh2)
	{
		//GEngine->AddOnScreenDebugMessage(1235, 100.0f, FColor::MakeRandomColor(), TEXT("FIRST IF OVERLAP"));
	}
	if (Mesh3)
	{
		if (Mesh3->GetName() == "CollisionCylinder")
		{
			//GEngine->AddOnScreenDebugMessage(1236, 100.0f, FColor::MakeRandomColor(), Mesh3->GetName());
			AIndividual* OverlappedAgent = Cast<AIndividual>(OtherActor);
			if (!Individuals.Contains(OverlappedAgent))
			{
				GEngine->AddOnScreenDebugMessage(1266, 100.0f, FColor::MakeRandomColor(), TEXT("DISTANCE DISTANCE DISTANCE DISTANCE "));

				ADissertationGameMode* GameMode = Cast<ADissertationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

				if (GameMode)
				{
					if (!BlackboardComp->GetValueAsBool("IsSelling"))
					{
						GameMode->IncreaseCollision(BuyingState);
						NumOfCollisions++;
					}
				}

				Individuals.Add(OtherActor);
				SetShouldDistance(true);
				//SetShouldDistance(false);
			}
		}
	}
	//AIndividual* Individual = Cast<AIndividual>(OtherActor);
}

void AIndividual::OnFrontalCollisionEndOverlap(UPrimitiveComponent* OverlappedComp,	AActor* OtherActor,	UPrimitiveComponent* OtherComp,	int32 OtherBodyIndex)
{
	AIndividual* OverlapActor = Cast<AIndividual>(OtherActor);

	if (OverlapActor)
	{
		if (Individuals.Contains(OverlapActor))
		{
			Individuals.Remove(OtherActor);
			if (Individuals.Num() == 0)
			{
				SetShouldDistance(false);
			}
		}
	}
}

FVector AIndividual::InLineLocation() const
{
	return InLineCapsule->GetComponentLocation();
}

TArray<AActor*> AIndividual::CheckSurroundings()
{
	TArray<AActor*> overlappedActors;
	SurroundingsCollisionCheck->GetOverlappingActors(overlappedActors, AIndividual::StaticClass());

	return overlappedActors;
}

void AIndividual::GenerateShoppingList()
{
	int listSize = FMath::RandRange(MinListSize, MaxListSize);

	for (int i = 0; i < listSize; i++)
	{
		int itemIndex = FMath::RandRange(0, static_cast<uint8>(EAisleType::MAX) - 1);
		ShoppingList.Add(static_cast<EAisleType>(itemIndex));
	}

	int stateMin = 0;
	int stateMax = static_cast<uint8>(EBuyingState::MAX) - 1;

	int state = FMath::RandRange(stateMin, stateMax);

	BuyingState = static_cast<EBuyingState>(state);
	ListSize = listSize;
}

bool AIndividual::GetShouldDistance() const
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsBool(ShouldDistanceKeyName);
	}

	return false;
}

void AIndividual::SetShouldDistance(bool value)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(ShouldDistanceKeyName, value);
	}
}