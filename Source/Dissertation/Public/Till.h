// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Till.generated.h"

UCLASS()
class DISSERTATION_API ATill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATill();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isCashOnly;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isFree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isSelfServe;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isOpen;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetClientTillCapsuleLocation() const;
	FVector GetWorkerTillCapsuleLocation() const;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* WorkerCapsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* ClientCapsule;

};
