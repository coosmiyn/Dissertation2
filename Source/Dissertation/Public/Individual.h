// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "STypes.h"
#include "DissertationGameMode.h"
#include "Kismet/GameplayStatics.h"

#include "Components/SphereComponent.h"

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

	TArray<EAisleType> ShoppingList;

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

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* FrontCollisionCheck;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* SurroundingsCollisionCheck;


	void GenerateShoppingList();

};
