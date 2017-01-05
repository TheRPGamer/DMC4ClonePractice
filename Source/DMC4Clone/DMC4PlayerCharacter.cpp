// Fill out your copyright notice in the Description page of Project Settings.

#include "DMC4Clone.h"

#include "DMC4EnemySpawner.h"

#include "DMC4PlayerCharacter.h"


// Sets default values
ADMC4PlayerCharacter::ADMC4PlayerCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw= false;
    bUseControllerRotationRoll = false;
    
    ThirdPersonSpringArm = CreateDefaultSubobject<USpringArmComponent>("ThirdPersonSpringArm");
    if(ThirdPersonSpringArm)
    {
        ThirdPersonSpringArm->SetupAttachment(RootComponent);
        ThirdPersonSpringArm->TargetArmLength = 250.0f;
        ThirdPersonSpringArm->bUsePawnControlRotation= true;
        ThirdPersonSpringArm->bAbsoluteRotation = false;
        ThirdPersonSpringArm->bAbsoluteLocation= false;
        ThirdPersonSpringArm->bInheritYaw = false;
        ThirdPersonSpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
    }
    
    ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>("ThirdPersonCamera");
    if(ThirdPersonCamera)
    {
        ThirdPersonCamera->SetupAttachment(ThirdPersonSpringArm, USpringArmComponent::SocketName);
        ThirdPersonCamera->SetProjectionMode(ECameraProjectionMode::Perspective) ;
        ThirdPersonCamera->bAbsoluteRotation = false;
        ThirdPersonCamera->bUsePawnControlRotation = false;
        ThirdPersonCamera->SetFieldOfView(120.0f);
        ThirdPersonCamera->SetRelativeRotation(FRotator(-25.0f, 0, 0));
    }
    
    if(GetCharacterMovement())
    {
        GetCharacterMovement()->bOrientRotationToMovement = true;
    }
    
}

void ADMC4PlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    
}

void ADMC4PlayerCharacter::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
}

void ADMC4PlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    if(PlayerInputComponent)
    {
		PlayerInputComponent->BindAxis("RotateCamera", this, &ADMC4PlayerCharacter::RotateCamera);
		PlayerInputComponent->BindAxis("MoveForward", this, &ADMC4PlayerCharacter::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &ADMC4PlayerCharacter::MoveRight);
        
		PlayerInputComponent->BindAction("LockOn", IE_Pressed, this, &ADMC4PlayerCharacter::LockOnPressed);
		PlayerInputComponent->BindAction("LockOn", IE_Released, this, &ADMC4PlayerCharacter::LockOnReleased);
    }
    else
    {
        UE_LOG(LogDMC, Warning, TEXT("Input Component is null in DMC4Character"));
    }
}

void ADMC4PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (NewController->IsPlayerController())
	{
		// TODO: LOG you shall not use the player character with any controller besides a player controller
	}

	auto World = GetWorld();
	if (World)
	{
		for (TActorIterator<ADMC4EnemySpawner> ActorItr(World); ActorItr; ++ActorItr)
		{
			(*ActorItr)->OnEnemySpawnedEvent.AddUObject(this, &ADMC4PlayerCharacter::OnEnemySpawnedEvent);
		}
	}
}

void ADMC4PlayerCharacter::OnEnemySpawnedEvent_Implementation(ADMC4EnemyCharacter* EnemyCharacter)
{
	// we expect a valid character at all times
	check(EnemyCharacter); 

	if (GEngine && EnemyCharacter)
	{
		// temporary testing
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Enemy %s spawned."), *EnemyCharacter->GetName()));
	}
}

void ADMC4PlayerCharacter::RotateCamera(float value)
{
    
    if(value)
    {
        AddControllerYawInput(value);
    }
}

void ADMC4PlayerCharacter::MoveForward(float value)
{
    if(value && ThirdPersonCamera)
    {
        FVector forward = ThirdPersonCamera->GetForwardVector();
        forward.Z=0;
        forward.Normalize();
        AddMovementInput(forward, value);
    }
}

void ADMC4PlayerCharacter::MoveRight(float value)
{
    if(value && ThirdPersonCamera)
    {
        FVector right = ThirdPersonCamera->GetRightVector();
        right.Z=0;
        right.Normalize();
        AddMovementInput(right, value);
    }
}

FVector ADMC4PlayerCharacter::GetRandomLocationFromPlayer() const
{
    FVector playerLocation = GetPlayerCurrentLocation();
    playerLocation.X = FMath::RandRange(playerLocation.X+300.0f, playerLocation.X+1300.0f);
    playerLocation.Y = FMath::RandRange(playerLocation.Y+300.0f, playerLocation.Y+1300.0f);
    
    playerLocation.Z = 200.0f;
    
    return playerLocation;
}

ADMC4EnemyCharacter* ADMC4PlayerCharacter::GetClosestEnemy() const
{
    ADMC4EnemyCharacter* closestEnemy = ArrayEnemies[0];
    float closestDistance = GetSquaredDistanceTo(closestEnemy);
    for(auto& enemy : ArrayEnemies)
    {
        float distance = GetSquaredDistanceTo(enemy);
        if(distance < closestDistance)
        {
            closestDistance = distance;
            closestEnemy = enemy; 
        }
    }
    
    return closestEnemy;
    
}

void ADMC4PlayerCharacter::LockOnPressed()
{
 
    if(ArrayEnemies.Num() == 0)
    {
        return;
    }
    OrientPlayerToEnemy(); 
    
}

void ADMC4PlayerCharacter::LockOnReleased()
{

}
void ADMC4PlayerCharacter::OrientPlayerToEnemy()
{
    auto enemy = GetClosestEnemy();
    FVector vector = enemy->GetActorLocation() - GetActorLocation();
    vector.Normalize();
    FVector forward = GetActorForwardVector();
    float dotProduct = FVector::DotProduct(vector, forward);
    float turnAngle = FMath::Acos(dotProduct); 
    turnAngle = FMath::RadiansToDegrees(turnAngle);
    FVector crossProduct = FVector::CrossProduct(vector, forward);
    FRotator rotation = Controller->GetControlRotation();
    FRotator currRotation =Controller->GetControlRotation();
    if(crossProduct.Z < 0)
    {
        rotation.Yaw += turnAngle;
    }
    else if(crossProduct.Z > 0)
    {
        rotation.Yaw-=turnAngle;
    }
    Controller->SetControlRotation(rotation);
}
