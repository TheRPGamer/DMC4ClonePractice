// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "DMC4Character.h"
#include "DMC4EnemyCharacter.h"
#include "DMC4PlayerCharacter.generated.h"




//Provides a way to aquire and release LockOn Mode for the player character. 
//A player can enter lock on mode at all times, even when there is no character to lock.
USTRUCT()
struct DMC4CLONE_API FDMC4LockedCharacter
{
	GENERATED_BODY()

public:	
	//Aquires a lock. Note param CharToLock is allowed to be null as we do not need a character to enter LockOn mode
	void AquireLock(ADMC4EnemyCharacter* CharToLock = nullptr) { bLockedOn = true, LockedCharacter = CharToLock; }

	//Releases the current lock and resets the locked character to nullptr in any case
	void ReleaseLock() { bLockedOn = false; LockedCharacter = nullptr; }

	//Returns true if lock is on (weather a char is locked or not)
	bool IsLocked() { return bLockedOn;  }

	//Gets the currently locked character. Returns nullptr if none is locked
	FORCEINLINE ADMC4EnemyCharacter* Get() const { return LockedCharacter; }
		

private:
	//Determines whether or not character is locked on to an enemy hence what attacks the player can do	
	bool bLockedOn = false;

	// the actual locked character (note we need to declare this UPROPERTY() so the garbage collection sees we reference it here
	UPROPERTY()
	ADMC4EnemyCharacter* LockedCharacter = nullptr;
};




//Defines a base for all characters that can be possessed by a player controller.
UCLASS()
class DMC4CLONE_API ADMC4PlayerCharacter : public ADMC4Character
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ADMC4PlayerCharacter();
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
	virtual void PossessedBy(AController* InController) override;
	
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
    
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
	UFUNCTION(BlueprintNativeEvent, Category = "DMC4PlayerCharacter")
	void OnEnemySpawnedEvent(ADMC4EnemyCharacter* EnemyCharacter);


    FORCEINLINE UCameraComponent* GetThirdPersonCamera() const
    {
        return ThirdPersonCamera;
    }
    
    UFUNCTION(BlueprintCallable, Category = "DMC4PlayerCharacter")
    FVector GetPlayerCurrentLocation() const
    {
        return GetActorLocation(RootComponent);
    }
    
    //returns a random location within an offset radisu of the player
    UFUNCTION(BlueprintCallable, Category = "DMC4PlayerCharacter")
    FVector GetRandomLocationFromPlayer() const;
    

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
    
    //Array of all enemies that have been spawned on current level (note we need to use UPROPERTY() here so the garbage collection sees our references)
	UPROPERTY()
    TArray<ADMC4EnemyCharacter*> ArrayEnemies;
    
	//The character that is currently locked
	FDMC4LockedCharacter LockedCharacter;  

    
};
