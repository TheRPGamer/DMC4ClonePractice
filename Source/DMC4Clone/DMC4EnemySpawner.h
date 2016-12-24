// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DMC4EnemySpawner.generated.h"

//Actor used to spawn all enemies in DMC4.
//EnemyBPClass must be set in Blueprints to select the enemy to be spanwed.
//As of now, only one type of enemy can be spawned per actor. 

UCLASS()
class DMC4CLONE_API ADMC4EnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADMC4EnemySpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
    
    UFUNCTION(BlueprintCallable, Category = "GetRandomLocation")
    FVector GetRandomLocationWithinSpawnSphere() const;
private:
    //Spawns an enemy given a random locaiton
    void SpawnEnemyAtLocation();
    
    //Function that takes in a UClass pointer to a BP and spawns it 
    class ADMC4EnemyCharacter* SpawnEnemyBP(UWorld* world, UClass* bpClass, FVector location, FRotator rotation, AActor* owner = nullptr, APawn* instigator = nullptr);
    
    
    //UClass pointer of the Test Enemy Class to use with SpawnBP.
    //Set in blueprint.
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TestEnemyClass", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class ADMC4EnemyCharacter> EnemyBPClass;
    
    //Timer to spawn enemies every few seconds at random locations from player
    FTimerHandle SpawnEnemyTimer;
    
    //Sphere Component where Enemies are allowed to spawn from
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category ="SpawnRange", meta = (AllowPrivateAccess = "true"))
    USphereComponent* SpawnSphere = nullptr;
    
    //radius of the Spawn Sphere
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SpawnSphere", meta = (AllowPrivateAccess = "true"))
    float SpawnSphereRadius = 100.0f; 
	
    
	
};
