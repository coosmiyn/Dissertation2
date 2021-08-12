// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

UENUM()
enum class EAisleType : uint8
{
	Food = 0,
	Bread = 1,
	Cupboard = 2,
	Cosmetics = 3,

	MAX = 4			UMETA(Hidden)
};

UENUM()
enum class EBuyingState : uint8
{
	FastBuy = 0,
	Explore = 1,

	MAX = 2			UMETA(Hidden)
};
