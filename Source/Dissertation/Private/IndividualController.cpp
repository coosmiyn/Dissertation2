// Fill out your copyright notice in the Description page of Project Settings.


#include "IndividualController.h"

AIndividualController::AIndividualController()
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
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AIndividualController::OnPawnDetected);

	//Called when sight is updated. Returns the target that updated it with the information about the sight updated. (Ex. Successfully sensed or not)
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AIndividualController::OnTargetDetected);

	// Configura/Initialize the sight
	GetPerceptionComponent()->ConfigureSense(*Sight);

	// Create the AI components
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

void AIndividualController::BeginPlay()
{
	Super::BeginPlay();
}

void AIndividualController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AIndividual* Individual = Cast<AIndividual>(InPawn);

	if (Individual)
	{
		if (Individual->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*Individual->BehaviorTree->BlackboardAsset);
		}

		BehaviorComp->StartTree(*Individual->BehaviorTree);
	}
}

void AIndividualController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AIndividualController::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{
}

void AIndividualController::OnTargetDetected(AActor* Actor, FAIStimulus const stimulus)
{
}

EAisleType AIndividualController::GetListItem() const
{
	if (BlackboardComp)
	{
		return static_cast<EAisleType>(BlackboardComp->GetValueAsEnum(ListItemKeyName));
	}
	return EAisleType::Bread;
}

void AIndividualController::SetListItem(EAisleType item)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsEnum(ListItemKeyName, static_cast<uint8>(item));
	}
}

AAisle* AIndividualController::GetNextAisle() const
{
	if (BlackboardComp)
	{
		return Cast<AAisle>(BlackboardComp->GetValueAsObject(NextAisleKeyName));
	}
	return nullptr;
}

void AIndividualController::SetNextAisle(AActor* actor)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(NextAisleKeyName, actor);
	}
}
