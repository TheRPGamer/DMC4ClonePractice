// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "DMC4Character.generated.h"

//Base class for all characters in DMC4 to inherit from

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

    UFUNCTION(BlueprintCallable, Category = "StatGetters")
    int32 GetMaxHP() const
    {
        return MaxHP;
    }
    
    UFUNCTION(BlueprintCallable, Category = "StatGetters")
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
