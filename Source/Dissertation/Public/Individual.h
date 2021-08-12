// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "STypes.h"
#include "DissertationGameMode.h"
#include "Kismet/GameplayStatics.h"

#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "Individual.generated.h"

UCLASS()
class DISSERTATION_API AIndividual : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AIndividual();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<EAisleType> ShoppingList;
	TArray<AActor*> Individuals;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
		void OnFrontalCollisionOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnFrontalCollisionEndOverlap(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MinListSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxListSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBuyingState BuyingState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FName ShouldDistanceKeyName;

	bool GetShouldDistance() const;
	void SetShouldDistance(bool value);

	bool GetIsInQueue() const { return isInQueue; };
	void SetIsInQueue(bool value) { isInQueue = value; };

	FVector InLineLocation() const;
	UCapsuleComponent* GetQueueComponent() const { return InLineCapsule; }
	void SetBlackboard(UBlackboardComponent* comp) { BlackboardComp = comp; }

	TArray<AActor*> CheckSurroundings();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FDateTime StartTime;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int NumOfCollisions;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FDateTime EndTime;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		FDateTime TimeSpentInside;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int ListSize;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* FrontCollisionCheck;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* SurroundingsCollisionCheck;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* InLineCapsule;


	void GenerateShoppingList();

	UBlackboardComponent* BlackboardComp;

	bool isInQueue = false;

};
