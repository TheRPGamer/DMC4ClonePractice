// Fill out your copyright notice in the Description page of Project Settings.

#include "DMC4Clone.h"
#include "DMC4EnemySpawner.h"
#include "DMC4PlayerCharacter.h"

// Sets default values
ADMC4EnemySpawner::ADMC4EnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
    if(Sphere)
    {
        RootComponent = Sphere;
        Sphere->InitSphereRadius(SphereRadius);
    }
    

}
#if WITH_EDITOR
void ADMC4EnemySpawner::PostEditChangeProperty(FPropertyChangedEvent& propertyChangedEvent)
{
    Super::PostEditChangeProperty(propertyChangedEvent);
    if(propertyChangedEvent.Property)
    {
        auto propertyName = propertyChangedEvent.Property->GetFName();
        if(propertyName == GET_MEMBER_NAME_CHECKED(ADMC4EnemySpawner, Sphere))
        {
            Sphere->SetSphereRadius(SphereRadius);
        }
    }
}
#endif

// Called when the game starts or when spawned
void ADMC4EnemySpawner::BeginPlay()
{
	Super::BeginPlay();
    PrimaryActorTick.TickInterval = TickInterval;
    //Wouldn't this prevent the need for the above function?
    Sphere->SetSphereRadius(SphereRadius);
    
    auto character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if(character)
    {
        Player = Cast<ADMC4PlayerCharacter>(character);
    }
    
}

// Called every frame
void ADMC4EnemySpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    if((SpawnMaxCurrent < SpawnMax) && (SpawnLimitCurrent < SpawnLimit))
    {
        SpawnEnemy();
    }
    
}

void ADMC4EnemySpawner::SpawnEnemy()
{
    UWorld* world = GetWorld();
    if(world)
    {
        FVector location = GetRandomLocationWithinSpawnSphere();
        FRotator rotation(0.0f, 0.0f, 0.0f);
        if(EnemyClassesToSpawn.Num() > 0)
        {
            for(auto const& spawnInfo : EnemyClassesToSpawn)
            {
                auto spawnChance = GetChanceToSpawn(spawnInfo);
                if(spawnChance > FMath::FRand())
                {
                    FActorSpawnParameters spawnParams;
                    spawnParams.bDeferConstruction = false;
                    auto enemy = Cast<ADMC4EnemyCharacter>(world->SpawnActor(spawnInfo.EnemyClass, &location, &rotation, spawnParams));
                    UE_LOG(LogTemp, Log,TEXT("The value of enemy is %p"), enemy);
                    //Where Delegate SHOULD broadcast, but I'm not
                    if(enemy)
                    {
                        //FUNCTION NAME IS NOT WHAT IT SEEMS
                        //Adds the enemy that's just spawnedto ArrayEnemy in Player
                        Player->BindOnEnemySpawnEvent(enemy);
                        ++SpawnLimitCurrent;
                        ++SpawnMaxCurrent;
                        //OnEnemySpawnedEvent.Broadcast(enemy);
                    }
                    
                    
                }
            }
        }
    }
    else
    {
        UE_LOG(LogDMC, Warning, TEXT("Warning, no enemy class in %s. Please assign some enemy classes."), *GetName());
    }
}

FVector ADMC4EnemySpawner::GetRandomLocationWithinSpawnSphere() const
{
    FVector location = GetActorLocation();
    location.X = FMath::RandRange(location.X, location.X + SphereRadius);
    location.Y = FMath::RandRange(location.Y, location.Y + SphereRadius);
    location.Z = 0.f;
    return location; 
}

float ADMC4EnemySpawner::GetChanceToSpawn(FDMC4EnemySpawnInfo const& spawnInfo)
{
    switch(spawnInfo.SpawnChance)
    {
        case EDMC4SpawnChance::VeryHigh :
        {
            return 0.99f;
            break;
        }
        case EDMC4SpawnChance::High :
        {
            return 0.75f;
            break;
        }
        case EDMC4SpawnChance::Normal :
        {
            return 0.5f;
            break;
        }
        case EDMC4SpawnChance::Low :
        {
            return 0.25f;
            break;
        }
        case EDMC4SpawnChance::VeryLow :
        {
            return 0.05;
            break;
        }
        default:
        {
            UE_LOG(LogDMC, Warning, TEXT("Unknown Enum used in %s. Please check input."), *GetName());
            break;
        }
    }
    return 0.0f;
}
