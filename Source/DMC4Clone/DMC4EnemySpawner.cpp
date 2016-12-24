// Fill out your copyright notice in the Description page of Project Settings.

#include "DMC4Clone.h"
#include "DMC4EnemySpawner.h"
#include "DMC4EnemyCharacter.h"

// Sets default values
ADMC4EnemySpawner::ADMC4EnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SpawnSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnSphere"));
    if(SpawnSphere)
    {
        RootComponent = SpawnSphere; 
        SpawnSphere->InitSphereRadius(SpawnSphereRadius);

    }
    
    
}

// Called when the game starts or when spawned
void ADMC4EnemySpawner::BeginPlay()
{
	Super::BeginPlay();
    
    UWorld* world = GetWorld();
    if(world)
    {
        world->GetTimerManager().SetTimer(SpawnEnemyTimer, this, &ADMC4EnemySpawner::SpawnEnemyAtLocation, 5.0f, true);
    }
}

// Called every frame
void ADMC4EnemySpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ADMC4EnemySpawner::SpawnEnemyAtLocation()
{
    UWorld* world = GetWorld();
    if(world)
    {
        FVector randomLocation = GetRandomLocationWithinSpawnSphere();
        FRotator enemyRotation(0.0f, 0.0f, 0.0f);
        SpawnEnemyBP(world, EnemyBPClass, randomLocation, enemyRotation);
    }
}

ADMC4EnemyCharacter* ADMC4EnemySpawner::SpawnEnemyBP(UWorld* world, UClass* bpClass, FVector location, FRotator rotation, AActor* owner, APawn* instigator)
{
    if(world && bpClass)
    {
        FActorSpawnParameters spawnParams;
        spawnParams.Owner = owner;
        spawnParams.Instigator = instigator;
        spawnParams.bDeferConstruction = false;
        
        auto enemy = Cast<ADMC4EnemyCharacter>(world->SpawnActor(bpClass, &location, &rotation, spawnParams ));
        if(enemy)
        {
            return enemy;
        }
    }
    UE_LOG(LogDMC, Warning, TEXT("EnemySpawner: Either world or BPClass is null while spawning enemy"));
    return nullptr; 
        
}

FVector ADMC4EnemySpawner::GetRandomLocationWithinSpawnSphere() const
{
    FVector location = GetActorLocation();
    location.X = FMath::RandRange(location.X, location.X + SpawnSphereRadius);
    location.Y = FMath::RandRange(location.Y, location.Y + SpawnSphereRadius);
    location.Z = 0.f;
    return location; 
}
