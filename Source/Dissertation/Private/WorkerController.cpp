// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkerController.h"

AWorkerController::AWorkerController()
{
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	// Setup the sight parameters
	Sight->SightRadius = AISightRadius;
	Sight->LoseSightRadius = AISightLoseRadius;
	Sight->PeripheralVisionAngleDegrees = AIFieldOfView;
	Sight->SetMaxAge(AISightAge);

	// What the pawn can detect
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;

	// Configure the pawn's sight
	GetPerceptionComponent()->SetDominantSense(*Sight->GetSenseImplementation());

	// Called when sight is updated. Returns an Array of all the actors which updated the sight. 
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AWorkerController::OnPawnDetected);

	//Called when sight is updated. Returns the target that updated it with the information about the sight updated. (Ex. Successfully sensed or not)
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AWorkerController::OnTargetDetected);

	// Configura/Initialize the sight
	GetPerceptionComponent()->ConfigureSense(*Sight);

	// Create the AI components
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

void AWorkerController::BeginPlay()
{
	Super::BeginPlay();
}

void AWorkerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AWorker* Worker = Cast<AWorker>(InPawn);

	if (Worker)
	{
		if (Worker->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*Worker->BehaviorTree->BlackboardAsset);
		}

		BehaviorComp->StartTree(*Worker->BehaviorTree);
	}
}

void AWorkerController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AWorkerController::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{
}

void AWorkerController::OnTargetDetected(AActor* Actor, FAIStimulus const stimulus)
{
}

ATill* AWorkerController::GetTill() const
{
	if (BlackboardComp)
	{
		return Cast<ATill>(BlackboardComp->GetValueAsObject(TillKeyName));
	}
	return nullptr;
}

void AWorkerController::SetTill(AActor* actor)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(TillKeyName, actor);
	}
}

FVector AWorkerController::GetTillWorkerCapsuleLocation() const
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsVector(TillWorkerCapsuleLocation);
	}
	return FVector();
}

void AWorkerController::SetTillWorkerCapsuleLocation(FVector location)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsVector(TillWorkerCapsuleLocation, location);
	}
}
