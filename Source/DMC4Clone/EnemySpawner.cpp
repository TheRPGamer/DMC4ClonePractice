// Fill out your copyright notice in the Description page of Project Settings.

#include "DMC4Clone.h"
#include "EnemySpawner.h"
#include "DMC4EnemyCharacter.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    static ConstructorHelpers::FObjectFinder<UBlueprint> EnemyBP(TEXT("Blueprint'/Game/TestEnemyCharacter.TestEnemyCharacter'"));

    if(EnemyBP.Object)
    {
        testClass = Cast<UClass>(EnemyBP.Object->GeneratedClass);
    }
    else
    {
        UE_LOG(LogDMC, Warning, TEXT("SpawnManager: EnemyBP reference not found!"));
    }
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
    
    UWorld* world = GetWorld();
    if(world)
    {
        world->GetTimerManager().SetTimer(SpawnEnemyTimer, this, &AEnemySpawner::SpawnEnemyAtLocation, 5.0f, true);
    }
}

// Called every frame
void AEnemySpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

FVector AEnemySpawner::GetRandomLocationFromPlayer()
{
    FVector playerLocation = GetPlayerCurrentLocation();
    playerLocation.X = FMath::RandRange(playerLocation.X+300.0f, playerLocation.X+1300.0f);
    playerLocation.Y = FMath::RandRange(playerLocation.Y+300.0f, playerLocation.Y+1300.0f);

    playerLocation.Z = 200.0f;
    
    return playerLocation; 
}

FVector AEnemySpawner::GetPlayerCurrentLocation()
{
    auto playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if(playerController)
    {
        return playerController->GetPawn()->GetActorLocation();
    }
    else
    {
        UE_LOG(LogDMC, Error, TEXT("Spawn Manager: Player Controller at index 0 not found."));
        return FVector(0.f, 0.f, 0.f);
    }
}

void AEnemySpawner::SpawnEnemyAtLocation()
{
    UWorld* world = GetWorld();
    if(world)
    {
        FVector randomLocation = GetRandomLocationFromPlayer();
        FRotator enemyRotation(0.0f, 0.0f, 0.0f);
        //UClass* enemyClass = (UClass*)EnemyBPClass;
        SpawnEnemyBP<ADMC4EnemyCharacter>(world, testClass, randomLocation, enemyRotation);
    }
}