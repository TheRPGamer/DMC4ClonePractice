// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DMC4EnemyCharacter.h"
#include "DMC4EnemySpawner.generated.h"


DECLARE_EVENT_OneParam(ADMC4EnemySpawner, FOnEnemySpawnedEvent, ADMC4EnemyCharacter*);

UENUM()
enum class EDMC4SpawnChance : uint8
{
    VeryLow,
    Low,
    Normal,
    High,
    VeryHigh,
};

//A struct that holds the Enemy Class to be spawned and the chance of it being spawned
USTRUCT()
struct FDMC4EnemySpawnInfo
{
    GENERATED_BODY()
    
    //The class the Enemy Belongs To
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnInfo")
    TSubclassOf<ADMC4EnemyCharacter> EnemyClass = nullptr;
    
    //Chance of the Enemy Spawning
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnInfo")
    EDMC4SpawnChance SpawnChance = EDMC4SpawnChance::Normal;

};


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

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& propertyChangedEvent) override;
#endif
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
    
    //Gets a random location within this actor
    UFUNCTION(BlueprintCallable, Category = "GetRandomLocation")
    FVector GetRandomLocationWithinSpawnSphere() const;
    
    //Array of EnemySpawnInfo, each with its own Spawn Class and Spawn Chance
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnemyClass")
    TArray<FDMC4EnemySpawnInfo> EnemyClassesToSpawn;
    
    //Event to be broadcasted when enemy is spawned
    FOnEnemySpawnedEvent OnEnemySpawnedEvent;
    
    //Internal Tick Value of the actor
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnemySpawner")
    float TickInterval = 5.0f;

private:
    //Returns spawn chance of an enemy from its enemy spawn info struct 
    float GetChanceToSpawn(FDMC4EnemySpawnInfo const& enemySpawnInfo);
    
    //Function that takes in a UClass pointer to a BP and spawns it 
    void SpawnEnemy();
    
    //Max number of enemies that can be spawned
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnInfo", meta = (AllowPrivateAccess = "true"))
    int32 SpawnMax = 5;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnOnfo", meta = (AllowPrivateAccess = "true"))
    int32 SpawnLimit = 2;
    
    //Current number of enemies spanwed
    //Decrements when an enemy is killed 
    int32 SpawnLimitCurrent = 0;
    
    //Current number of enemies spawned
    int32 SpawnMaxCurrent = 0;
    
    //Sphere Component where Enemies are allowed to spawn from
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category ="SpawnRange",
              meta = (AllowPrivateAccess = "true"))
    USphereComponent* Sphere = nullptr;
    
    //radius of the Spawn Sphere
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnSphere", meta = (AllowPrivateAccess = "true"))
    float SphereRadius = 100.0f;
    
    //Keeps track of the player 
    class ADMC4PlayerCharacter* Player;
	
    
	
};
