// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CheckSurroundings.h"

#include "Individual.h"
#include "IndividualController.h"
#include "DissertationGameMode.h"

EBTNodeResult::Type UBTTask_CheckSurroundings::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIndividual* Individual;
	AIndividualController* Controller = Cast<AIndividualController>(OwnerComp.GetAIOwner());

	if (Controller)
	{
		Individual = Cast<AIndividual>(Controller->GetPawn());

		TArray<AActor*> overlappedActors = Individual->CheckSurroundings();

		if (overlappedActors.Num() == 0)
		{
			Controller->SetShouldDistance(false);
			return EBTNodeResult::Succeeded;
		}
		else
		{
			ADissertationGameMode* GameMode = Cast<ADissertationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
			if (GameMode)
			{
				GameMode->IncreaseCollision(Individual->BuyingState);
			}
		}
	}

	return EBTNodeResult::Failed;
}