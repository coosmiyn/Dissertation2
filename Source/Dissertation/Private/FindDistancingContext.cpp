// Fill out your copyright notice in the Description page of Project Settings.


#include "FindDistancingContext.h"

#include "EnvironmentQuery/EnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

#include "Individual.h"
#include "IndividualController.h"

void UFindDistancingContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	AIndividualController* Controller = Cast<AIndividualController>((Cast<AActor>((QueryInstance.Owner).Get())->GetInstigatorController()));
	AIndividual* Individual;

	if (Controller)
	{
		Individual = Cast<AIndividual>(Controller->GetPawn());

		UEnvQueryItemType_Actor::SetContextHelper(ContextData, Individual->Individuals);
	}
}