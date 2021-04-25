// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindClosedTill.h"

#include "Kismet/GameplayStatics.h"
#include "Till.h"

#include "Worker.h"
#include "WorkerController.h"

EBTNodeResult::Type UBTTask_FindClosedTill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AWorkerController* Controller = Cast<AWorkerController>(OwnerComp.GetAIOwner());
	AWorker* Worker;

	if (Controller)
	{
		Worker = Cast<AWorker>(Controller->GetPawn());

		TArray<AActor*> allTillActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATill::StaticClass(), allTillActors);

		for (AActor* tillActor : allTillActors)
		{
			ATill* Till = Cast<ATill>(tillActor);
			if (Till)
			{
				if (!Till->isOpen && !Till->isSelfServe)
				{
					Controller->SetTill(tillActor);
					Controller->SetTillWorkerCapsuleLocation(Till->GetWorkerTillCapsuleLocation());

					return EBTNodeResult::Succeeded;
				}
			}
		}
	}

	return EBTNodeResult::Failed;
}