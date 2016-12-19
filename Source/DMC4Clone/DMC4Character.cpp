// Fill out your copyright notice in the Description page of Project Settings.

#include "DMC4Clone.h"
#include "DMC4Character.h"


// Sets default values
ADMC4Character::ADMC4Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SetRootComponent(GetMesh());
    ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>("ThirdPersonCamera");
    ThirdPersonSpringArm = CreateDefaultSubobject<USpringArmComponent>("ThirdPersonSpringArm");
    
    ThirdPersonCamera->SetProjectionMode(ECameraProjectionMode::Perspective);
    ThirdPersonCamera->SetFieldOfView(120.0f);
    
    ThirdPersonSpringArm->TargetArmLength = 300.0f;
    ThirdPersonCamera->bUsePawnControlRotation = true;
    ThirdPersonSpringArm->SetupAttachment(RootComponent);
    ThirdPersonCamera->SetupAttachment(ThirdPersonSpringArm); 
    
    
    

}

// Called when the game starts or when spawned
void ADMC4Character::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ADMC4Character::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ADMC4Character::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

