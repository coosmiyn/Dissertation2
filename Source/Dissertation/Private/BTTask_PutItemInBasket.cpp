// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PutItemInBasket.h"

#include "Individual.h"
#include "IndividualController.h"
#include "STypes.h"
#include "Aisle.h"

EBTNodeResult::Type UBTTask_PutItemInBasket::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIndividualController* Controller = Cast<AIndividualController>(OwnerComp.GetAIOwner());
	AIndividual* Individual;

	if (Controller)
	{
		Individual = Cast<AIndividual>(Controller->GetPawn());

		if (Individual->BuyingState == EBuyingState::Explore)
		{
			AAisle* Aisle = Controller->GetNextAisle();
			for (EAisleType item : Individual->ShoppingList)
			{
				if (item == Aisle->AisleType)
				{
					Individual->ShoppingList.Remove(item);
				}
			}

			if (Individual->ShoppingList.Num() == 0)
			{
				Controller->SetIsShopping(false);
				Controller->SetIsLookingForTill(true);
			}
		}

		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}