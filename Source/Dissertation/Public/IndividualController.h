// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "Individual.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Touch.h"
#include "Perception/AISenseConfig_Damage.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "IndividualController.generated.h"

/**
 * 
 */
UCLASS()
class DISSERTATION_API AIndividualController : public AAIController
{
	GENERATED_BODY()

public:

	AIndividualController();

protected:

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

	//virtual FRotator GetControlRotation() const override;

	UFUNCTION()
		void OnPawnDetected(const TArray<AActor*>& DetectedPawns);

	UFUNCTION()
		void OnTargetDetected(AActor* Actor, FAIStimulus const stimulus);

public:
	// AI Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		UBehaviorTreeComponent* BehaviorComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		UBlackboardComponent* BlackboardComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		class UAISenseConfig_Sight* Sight;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		class UAISenseConfig_Hearing* Hearing;*/
		// Sight variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float AISightRadius = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float AISightAge = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float AISightLoseRadius = AISightRadius + 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float AIFieldOfView = 60.0f;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI)
	//	float HearingRange = 2000.0f;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI)
	//	float HearingAge = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FName ListItemKeyName;

	EAisleType GetListItem() const;
	void SetListItem(EAisleType item);

	FORCEINLINE UBehaviorTreeComponent* GetBehaviourComp() const { return BehaviorComp; }

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }

};
