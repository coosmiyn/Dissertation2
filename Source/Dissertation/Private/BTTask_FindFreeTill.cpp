// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindFreeTill.h"

#include "Kismet/GameplayStatics.h"
#include "Till.h"

#include "Individual.h"
#include "IndividualController.h"

EBTNodeResult::Type UBTTask_FindFreeTill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIndividualController* Controller = Cast<AIndividualController>(OwnerComp.GetAIOwner());
	AIndividual* Individual;

	if (Controller)
	{
		Individual = Cast<AIndividual>(Controller->GetPawn());

		TArray<AActor*> allTillActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATill::StaticClass(), allTillActors);

		for (AActor* tillActor : allTillActors)
		{
			ATill* Till = Cast<ATill>(tillActor);
			if (Till)
			{
				if (Till->isFree)
				{
					Controller->SetTill(tillActor);
					Controller->SetTillClientCapsuleLocation(Till->GetClientTillCapsuleLocation());

					return EBTNodeResult::Succeeded;
				}
			}
		}
	}

	return EBTNodeResult::Failed;
}