// Fill out your copyright notice in the Description page of Project Settings.

#include "DMC4Clone.h"


#include "DMC4EnemyCharacter.h"


ADMC4EnemyCharacter::ADMC4EnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ADMC4EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADMC4EnemyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}
