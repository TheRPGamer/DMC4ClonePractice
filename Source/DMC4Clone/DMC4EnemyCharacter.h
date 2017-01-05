// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DMC4Character.h"
#include "DMC4EnemyCharacter.generated.h"

//Base class for all Enemies in DMC4 
//TODO: ensure we cannot possess this with player controllers
UCLASS()
class DMC4CLONE_API ADMC4EnemyCharacter : public ADMC4Character
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADMC4EnemyCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
};
