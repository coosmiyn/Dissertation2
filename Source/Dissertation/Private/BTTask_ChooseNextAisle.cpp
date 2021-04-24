// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChooseNextAisle.h"

#include "Aisle.h"
#include "Kismet/GameplayStatics.h"

#include "Individual.h"
#include "IndividualController.h"

EBTNodeResult::Type UBTTask_ChooseNextAisle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIndividualController* Controller = Cast<AIndividualController>(OwnerComp.GetAIOwner());
	AIndividual* Individual;

	if (Controller)
	{
		Individual = Cast<AIndividual>(Controller->GetPawn());

		TArray<AActor*> allAisleActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAisle::StaticClass(), allAisleActors);

		for (AActor* aisleActor : allAisleActors)
		{
			AAisle* Aisle = Cast<AAisle>(aisleActor);
			if (Aisle)
			{
				EAisleType neededItem = Controller->GetListItem();
				if (Aisle->AisleType == neededItem)
				{
					Controller->SetNextAisle(aisleActor);
					return EBTNodeResult::Succeeded;
				}
			}
		}
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}