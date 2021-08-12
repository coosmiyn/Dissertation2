// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "Individual.h"
#include "Aisle.h"
#include "Till.h"
#include "Exit.h"
#include "Components/CapsuleComponent.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FName NextAisleKeyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FName TillKeyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FName TillClientCapsuleLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FName IsFirstKeyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FName IsWaitingInLineKeyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FName QueueLocationKeyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FName QueueComponentKeyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FName ListSizeKeyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FName IsSellingKeyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FName HasFinishedSellingKeyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FName IsShoppingKeyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FName VisitedAislesNumberKeyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FName ItemsBoughtKeyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FName ExitKeyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FName ShouldExitKeyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FName ShouldDistanceKeyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FName IsLookingForTillKeyName;

	EAisleType GetListItem() const;
	void SetListItem(EAisleType item);

	AAisle* GetNextAisle() const;
	void SetNextAisle(AActor* actor);

	ATill* GetTill() const;
	void SetTill(AActor* actor);

	FVector GetTillClientCapsuleLocation() const;
	void SetTillClientCapsuleLocation(FVector location);

	bool GetIsFirst() const;
	void SetIsFirst(bool value);

	bool GetIsWaitingInLine() const;
	void SetIsWaitingInLine(bool value);

	FVector GetQueueLocation() const;
	void SetQueueLocation(FVector location);

	UCapsuleComponent* GetQueueComponent() const;
	void SetQueueComponent(UCapsuleComponent* component);

	int GetListSize() const;
	void SetListSize(int value);

	bool GetIsSelling() const;
	void SetIsSelling(bool value);

	bool GetHasFinishedSelling() const;
	void SetHasFinishedSelling(bool value);

	bool GetIsShopping() const;
	void SetIsShopping(bool value);

	int GetVisitedAislesNumber() const;
	void SetVisitedAislesNumber(int value);

	int GetItemsBought() const;
	void SetItemsBought(int value);
	
	AExit* GetExit() const;
	void SetExit(AExit* actor);

	bool GetShouldExit() const;
	void SetShouldExit(bool value);

	bool GetShouldDistance() const;
	void SetShouldDistance(bool value);

	bool GetIsLookingForTill() const;
	void SetIsLookingForTill(bool value);

	FORCEINLINE UBehaviorTreeComponent* GetBehaviourComp() const { return BehaviorComp; }

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }

};
