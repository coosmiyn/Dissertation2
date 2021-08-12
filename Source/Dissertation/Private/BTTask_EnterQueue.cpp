// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_EnterQueue.h"

#include "Kismet/GameplayStatics.h"
#include "Till.h"

#include "DrawDebugHelpers.h"

#include "Individual.h"
#include "IndividualController.h"

EBTNodeResult::Type UBTTask_EnterQueue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIndividualController* Controller = Cast<AIndividualController>(OwnerComp.GetAIOwner());
	AIndividual* Individual;

	if (Controller)
	{
		Individual = Cast<AIndividual>(Controller->GetPawn());
		ATill* Till = Controller->GetTill();
		//bool isFirst = Till->EnrollInQueue(Individual);
		int numberOfPersonsInQueue = Till->EnrollInQueue2(Individual);
		bool isTheirTurn = Till->GetIsFirst(Individual);


		/*if (isFirst)
		{
		}*/

		int listSize = Individual->ShoppingList.Num();

		FVector QueueLocation = Till->GetQueueLocation();
		FVector QueueOffset = FVector(-Till->QueueDistance, 0.0f, 0.0f);
		FVector NewQueue;
		//if (numberOfPersonsInQueue != 0)
		QueueLocation.X -= (numberOfPersonsInQueue - 1) * Till->QueueDistance;
		NewQueue = FVector(QueueLocation.X, QueueLocation.Y, QueueLocation.Z);
		//DrawDebugSphere(GetWorld(), NewQueue, 100.0f, 27, FColor::Red, false, 300.0f);
		int id1 = FMath::RandRange(-100, 100);
		int id2 = FMath::RandRange(-100, 100);
		//GEngine->AddOnScreenDebugMessage(id1, 30.0f, FColor::MakeRandomColor(), TEXT("QUEUE LOCATION"));
		//GEngine->AddOnScreenDebugMessage(id2, 30.0f, FColor::MakeRandomColor(), FString::FromInt(numberOfPersonsInQueue));
	/*	int id3 = FMath::RandRange(-100, 100);
		int id4 = FMath::RandRange(-100, 100);
		GEngine->AddOnScreenDebugMessage(id3, 30.0f, FColor::MakeRandomColor(), TEXT("PersonsInQueue"));
		GEngine->AddOnScreenDebugMessage(id4, 30.0f, FColor::MakeRandomColor(), NewQueue.ToString());*/
		Controller->SetQueueLocation(NewQueue);
		//Controller->SetIsWaitingInLine(!isFirst);
		//Controller->SetIsFirst(isFirst);
		Controller->SetListSize(listSize);
		Controller->SetQueueComponent(Till->GetQueueComponent());
		if (isTheirTurn)
		{
			Controller->SetIsSelling(true);
			Controller->SetIsLookingForTill(false);
		}
		
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}