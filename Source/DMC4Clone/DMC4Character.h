// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "DMC4Character.generated.h"

/*
 * Base class of both playable characters and enemy characteres in DMC4Clone
 */
UCLASS()
class DMC4CLONE_API ADMC4Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADMC4Character();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
    
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    UFUNCTION(BlueprintCallable, Category = "StatGetters")
    int32 GetMaxHP() const
    {
        return MaxHP;
    }
    
    int32 GetCurrentHP() const
    {
        return CurrentHP;
    }
    
protected:
    //Maximum HP of character
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Stats", meta = (AllowProtectedAccess = "true"))
    int32 MaxHP;
    
    //Current HP of Character
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Stats", meta = (AllowProtectedAccess = "true"))
    int32 CurrentHP;
                                                                                          
                                                                                          
	
};
