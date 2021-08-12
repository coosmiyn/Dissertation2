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

	GEngine->AddOnScreenDebugMessage(245, 3.0f, FColor::MakeRandomColor(), TEXT("POSSESSING"));

	if (Individual)
	{
		if (Individual->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*Individual->BehaviorTree->BlackboardAsset);
		}

		BehaviorComp->StartTree(*Individual->BehaviorTree);
		Individual->SetBlackboard(BlackboardComp);

		SetIsShopping(true);
		
		TArray<AActor*> exitActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AExit::StaticClass(), exitActors);

		for (AActor* exitActor : exitActors)
		{
			AExit* Exit = Cast<AExit>(exitActor);
			if (Exit)
			{
				SetExit(Exit);
			}
		}
		//SetVisitedAislesNumber(0);
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

ATill* AIndividualController::GetTill() const
{
	if (BlackboardComp)
	{
		return Cast<ATill>(BlackboardComp->GetValueAsObject(TillKeyName));
	}
	return nullptr;
}

void AIndividualController::SetTill(AActor* actor)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(TillKeyName, actor);
	}
}

FVector AIndividualController::GetTillClientCapsuleLocation() const
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsVector(TillClientCapsuleLocation);
	}
	return FVector();
}

void AIndividualController::SetTillClientCapsuleLocation(FVector location)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsVector(TillClientCapsuleLocation, location);
	}
}

bool AIndividualController::GetIsFirst() const
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsBool(IsFirstKeyName);
	}
	
	return false;
}

void AIndividualController::SetIsFirst(bool value)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(IsFirstKeyName, value);
	}
}

bool AIndividualController::GetIsWaitingInLine() const
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsBool(IsWaitingInLineKeyName);
	}

	return false;
}

void AIndividualController::SetIsWaitingInLine(bool value)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(IsWaitingInLineKeyName, value);
	}
}

FVector AIndividualController::GetQueueLocation() const
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsVector(QueueLocationKeyName);
	}

	return FVector();
}

void AIndividualController::SetQueueLocation(FVector location)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsVector(QueueLocationKeyName, location);
	}
}

UCapsuleComponent* AIndividualController::GetQueueComponent() const
{
	if (BlackboardComp)
	{
		return Cast<UCapsuleComponent>(BlackboardComp->GetValueAsObject(QueueComponentKeyName));
	}

	return nullptr;
}

void AIndividualController::SetQueueComponent(UCapsuleComponent* component)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(QueueComponentKeyName, component);
	}
}

int AIndividualController::GetListSize() const
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsInt(ListSizeKeyName);
	}

	return 0;
}

void AIndividualController::SetListSize(int value)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsInt(ListSizeKeyName, value);
	}
}

bool AIndividualController::GetIsSelling() const
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsBool(IsSellingKeyName);
	}
	
	return false;
}

void AIndividualController::SetIsSelling(bool value)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(IsSellingKeyName, value);
	}
}

bool AIndividualController::GetHasFinishedSelling() const
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsBool(HasFinishedSellingKeyName);
	}

	return false;
}

void AIndividualController::SetHasFinishedSelling(bool value)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(HasFinishedSellingKeyName, value);
	}
}

bool AIndividualController::GetIsShopping() const
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsBool(IsShoppingKeyName);
	}

	return false;
}

void AIndividualController::SetIsShopping(bool value)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(IsShoppingKeyName, value);
	}
}

int AIndividualController::GetVisitedAislesNumber() const
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsInt(VisitedAislesNumberKeyName);
	}

	return 0;
}

void AIndividualController::SetVisitedAislesNumber(int value)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsInt(VisitedAislesNumberKeyName, GetVisitedAislesNumber() + 1);
	}
}

int AIndividualController::GetItemsBought() const
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsInt(ItemsBoughtKeyName);
	}
	
	return 0;
}

void AIndividualController::SetItemsBought(int value)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsInt(ItemsBoughtKeyName, GetItemsBought() + 1);
	}
}

AExit* AIndividualController::GetExit() const
{
	if (BlackboardComp)
	{
		return Cast<AExit>(BlackboardComp->GetValueAsObject(ExitKeyName));
	}

	return nullptr;
}

void AIndividualController::SetExit(AExit* actor)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(ExitKeyName, actor);
	}
}

bool AIndividualController::GetShouldExit() const
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsBool(ShouldExitKeyName);
	}

	return false;
}

void AIndividualController::SetShouldExit(bool value)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(ShouldExitKeyName, value);
	}
}

bool AIndividualController::GetShouldDistance() const
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsBool(ShouldDistanceKeyName);
	}

	return false;
}

void AIndividualController::SetShouldDistance(bool value)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(ShouldDistanceKeyName, value);
	}
}

bool AIndividualController::GetIsLookingForTill() const
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsBool(IsLookingForTillKeyName);
	}

	return false;
}

void AIndividualController::SetIsLookingForTill(bool value)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(IsLookingForTillKeyName, value);
	}
}
