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

	FrontOfLine = nullptr;
	hasQueue = false;
	PersonsInLine.Empty();
	QueueDistance = 180.0f;
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

bool ATill::EnrollInQueue(AIndividual* individual)
{
	bool isFirst = false;
	if (!PersonsInLine.Contains(individual))
	{
		PersonsInLine.Add(individual);
	}
	if (FrontOfLine == nullptr)
	{
		FrontOfLine = individual;
		if (PersonsInLine.Num() > 1)
		{
			GEngine->AddOnScreenDebugMessage(23, 3.0f, FColor::MakeRandomColor(), TEXT("ENTERED IF11"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(23, 3.0f, FColor::MakeRandomColor(), TEXT("ENTERED IF22"));
			isFirst = true;
		}
	}
	
	return isFirst;
}

int ATill::EnrollInQueue2(AIndividual* individual)
{
	if (!PersonsInLine.Contains(individual))
	{
		PersonsInLine.Add(individual);
		return PersonsInLine.Num();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(245, 30.0f, FColor::MakeRandomColor(), TEXT("RETURN QUEUE"));
		GEngine->AddOnScreenDebugMessage(246, 30.0f, FColor::MakeRandomColor(), FString::FromInt(PersonsInLine.IndexOfByKey(individual)));
		return PersonsInLine.IndexOfByKey(individual);
	}
	if (FrontOfLine == nullptr)
	{
		FrontOfLine = individual;
		if (PersonsInLine.Num() > 1)
		{
			GEngine->AddOnScreenDebugMessage(23, 3.0f, FColor::MakeRandomColor(), TEXT("ENTERED IF11"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(23, 3.0f, FColor::MakeRandomColor(), TEXT("ENTERED IF22"));
		}
	}

	return PersonsInLine.Num();
}

bool ATill::GetIsFirst(AIndividual* individual)
{
	if (PersonsInLine[0] == individual)
	{
		return true;
	}

	return false;
}

void ATill::LeaveQueue(AIndividual* individual)
{
	if (PersonsInLine.Contains(individual))
	{
		PersonsInLine.Remove(individual);
	}

	if (FrontOfLine == individual)
	{
		FrontOfLine = nullptr;
	}
}

FVector ATill::GetQueueLocation() const
{
	/*if (PersonsInLine.Num() > 1)
	{
		GEngine->AddOnScreenDebugMessage(54, 3.0f, FColor::MakeRandomColor(), TEXT("RETURN !!!"));
		return PersonsInLine[PersonsInLine.Num() - 1]->InLineLocation();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(55, 3.0f, FColor::MakeRandomColor(), TEXT("RETURN 222!!!"));
		return GetClientTillCapsuleLocation();
	}*/
	return ClientCapsule->GetComponentLocation();
}

UCapsuleComponent* ATill::GetQueueComponent() const
{
	if (FrontOfLine != nullptr)
	{
		return PersonsInLine[PersonsInLine.Num() - 1]->GetQueueComponent();
	}
	else
	{
		return ClientCapsule;
	}

	return nullptr;
}

