// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChooseNextAisle.h"

#include "Aisle.h"
#include "Kismet/GameplayStatics.h"
#include "Entrance.h"

#include "IndividualController.h"

EBTNodeResult::Type UBTTask_ChooseNextAisle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIndividualController* Controller = Cast<AIndividualController>(OwnerComp.GetAIOwner());
	AIndividual* Individual;
	AEntrance* Entrance;

	if (Controller)
	{
		Individual = Cast<AIndividual>(Controller->GetPawn());

		TArray<AActor*> allAisleActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAisle::StaticClass(), allAisleActors);

		TArray<AActor*> entranceActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEntrance::StaticClass(), entranceActors);

		for (AActor* entranceActor : entranceActors)
		{
			Entrance = Cast<AEntrance>(entranceActor);
			if (Entrance)
			{
				allAisleActors.Sort([Entrance](AActor& LHS, AActor& RHS)
					{
						float distance1 = FVector::Distance(LHS.GetActorLocation(), Entrance->GetActorLocation());
						float distance2 = FVector::Distance(RHS.GetActorLocation(), Entrance->GetActorLocation());
						return distance1 < distance2;
					});
			}

			for (AActor* actor : allAisleActors)
			{
				int id = FMath::RandRange(-100, 100);
				//GEngine->AddOnScreenDebugMessage(id, 300.0f, FColor::MakeRandomColor(), actor->GetName());
			}
		}

		if (Individual->BuyingState == EBuyingState::FastBuy)
		{
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
		}
		else if (Individual->BuyingState == EBuyingState::Explore)
		{
			int index = Controller->GetVisitedAislesNumber();
			if (index < allAisleActors.Num())
			{
				AActor* aisleActor = allAisleActors[index];
				AAisle* Aisle = Cast<AAisle>(aisleActor);
				if (Aisle)
				{
					Controller->SetNextAisle(aisleActor);
					Controller->SetVisitedAislesNumber(0);
					return EBTNodeResult::Succeeded;
				}
				else
				{
					Controller->SetIsShopping(false);
					Controller->SetIsLookingForTill(true);
				}
			}
			else
			{
				Controller->SetIsShopping(false);
				Controller->SetIsLookingForTill(true);
			}

			return EBTNodeResult::Succeeded;
		}

		GEngine->AddOnScreenDebugMessage(3456, 300.0f, FColor::MakeRandomColor(), TEXT("FAILED THE FUCKING TASK"));
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}

void UBTTask_ChooseNextAisle::SortAisles(TArray<AActor*> aisles, AIndividual* individual)
{
	/*TArray<AActor*> sortedAisles;
	for (AActor* aisleActor : aisles)
	{
		float distanceMin = 0;
		AAisle* Aisle = Cast<AAisle>(aisleActor);
		if (Aisle)
		{
			float distance = FVector::Distance(Aisle->GetActorLocation(), individual->GetActorLocation());
			if (distanceMin != 0)
			{
				distanceMin = distance;
			}
			else if (distance < distanceMin)
			{

			}
		}
	}*/
	/*aisles.Sort([individual](const FVector& LHS, const FVector& RHS) 
		{ 
			float distance1 = FVector::Distance(LHS, individual->GetActorLocation());
			float distance2 = FVector::Distance(RHS, individual->GetActorLocation());
			return distance1 > distance2; 
		});*/
}