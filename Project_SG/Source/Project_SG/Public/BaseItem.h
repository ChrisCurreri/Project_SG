// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInteractable.h"
#include "BaseItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_SG_API ABaseItem : public ABaseInteractable
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//virtual void SetupWigetClass() override;
};
