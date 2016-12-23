// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class DMC4CLONE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
    
private:
    //returns a random location from the player's current location
    FVector GetRandomLocationFromPlayer();
    
    //return player character's current location
    FVector GetPlayerCurrentLocation();
    
    //Spawns an enemy given a random locaiton
    void SpawnEnemyAtLocation();
    
    
    
    //template function to spawn different blueprint enemies as needed
    template <class T>
    FORCEINLINE T* SpawnEnemyBP(UWorld* World, UClass* BPClass, FVector Location, FRotator Rotation, AActor* Owner = nullptr, APawn* Instigator = nullptr)
    {
        if(!World)
        {
            return nullptr;
        }
        
        if(!BPClass)
        {
            return nullptr;
        }
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = Owner;
        SpawnParams.Instigator = Instigator;
        SpawnParams.bDeferConstruction = false;
        
        return World->SpawnActor<T>(BPClass, Location, Rotation, SpawnParams );
        
    }
    
    //UClass pointer of the Test Enemy Class to use with SpawnBP
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TestEnemyClass", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class ADMC4Enemy> EnemyBPClass;
    
    //Timer to spawn enemies every few seconds at random locations from player
    FTimerHandle SpawnEnemyTimer; 
	
    //temp var to test Template Class
    UClass* testClass = nullptr;
	
};
