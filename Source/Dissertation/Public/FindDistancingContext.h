// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "FindDistancingContext.generated.h"

/**
 * 
 */
UCLASS()
class DISSERTATION_API UFindDistancingContext : public UEnvQueryContext
{
	GENERATED_BODY()
	

protected:
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
};
