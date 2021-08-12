// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindFreeTill.h"

#include "Kismet/GameplayStatics.h"
#include "Till.h"

#include "Entrance.h"

#include "Individual.h"
#include "IndividualController.h"

EBTNodeResult::Type UBTTask_FindFreeTill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIndividualController* Controller = Cast<AIndividualController>(OwnerComp.GetAIOwner());
	AIndividual* Individual;

	if (Controller)
	{
		Individual = Cast<AIndividual>(Controller->GetPawn());

		if (!Individual->GetIsInQueue())
		{

			TArray<AActor*> allTillActors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATill::StaticClass(), allTillActors);

			TArray<AActor*> entranceActors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEntrance::StaticClass(), entranceActors);

			AActor* Entrance = entranceActors[0];

			allTillActors.Sort([Entrance](AActor& LHS, AActor& RHS)
				{
					float distance1 = FVector::Distance(LHS.GetActorLocation(), Entrance->GetActorLocation());
					float distance2 = FVector::Distance(RHS.GetActorLocation(), Entrance->GetActorLocation());
					ATill* till1 = Cast<ATill>(&LHS);
					ATill* till2 = Cast<ATill>(&RHS);
					int personsInLine1 = till1->GetNumberOfPersonsInLine();
					int personsInLine2 = till2->GetNumberOfPersonsInLine();
					return personsInLine1 < personsInLine2;
				});

			for (AActor* tillActor : allTillActors)
			{
				ATill* Till = Cast<ATill>(tillActor);
				if (Till)
				{
					if (Till->isFree && Till->isOpen)
					{
						Controller->SetTill(tillActor);
						Controller->SetTillClientCapsuleLocation(Till->GetClientTillCapsuleLocation());
						Individual->SetIsInQueue(true);

						return EBTNodeResult::Succeeded;
					}
				}
			}
		}
		else
		{
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}