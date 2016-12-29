// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "DMC4Character.h"
#include "DMC4EnemyCharacter.h"
#include "DMC4PlayerCharacter.generated.h"

//Base class for all playable characters in DMC4

UCLASS()
class DMC4CLONE_API ADMC4PlayerCharacter : public ADMC4Character
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ADMC4PlayerCharacter();
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
    
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    
    FORCEINLINE UCameraComponent* GetThirdPersonCamera() const
    {
        return ThirdPersonCamera;
    }
    
    UFUNCTION(BlueprintCallable, Category = "PlayerLocation")
    FVector GetPlayerCurrentLocation() const
    {
        return GetActorLocation(RootComponent);
    }
    
    //returns a random location within an offset radisu of the player
    UFUNCTION(BlueprintCallable, Category = "PlayerLocation")
    FVector GetRandomLocationFromPlayer() const;
    
    //Function to be bound to Enemy Spawner Delegate
    //Adds the enemy that is spawned to ArrayEnemies
    UFUNCTION()
    void BindOnEnemySpawnEvent(ADMC4EnemyCharacter* enemy);
private:
    //Rotates Third Person Camera around Character like orbit camera
    void RotateCamera(float value);
    
    //Moves character forward based on Third Person Camera forward vector. W for forward, S for back.
    void MoveForward(float value);
    
    //Moves character right based on Third Person Camera current right vector. D for right, A for left.
    void MoveRight(float value);
    
    //Called when lockon button pressed
    //Calls GetClosestEnemy() and OrientToEnemy()
    void LockOnPressed();
    
    //Called when LockOn button is realeased.
    void LockOnReleased();

    //Runs through all enemies in ArrayEnemies and returns closest
    ADMC4EnemyCharacter* GetClosestEnemy() const;
    
    //Turns the player to face closest enemy
    void OrientPlayerToEnemy();
 
    //Camera Component in 3rd Person Perspective to character
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    UCameraComponent* ThirdPersonCamera = nullptr;
    
    //Camera Boom to 3rd Person Camera
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* ThirdPersonSpringArm = nullptr;
    
    //Array of all enemies that have been spawned on current level 
    TArray<ADMC4EnemyCharacter*> ArrayEnemies;
    
    //Determines whether or not character is locked on to an enemy
    //Determines what attacks the player can do
    bool bLockedOn = false;
    
    
    
};
