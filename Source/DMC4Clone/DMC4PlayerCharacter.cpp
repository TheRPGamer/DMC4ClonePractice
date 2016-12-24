// Fill out your copyright notice in the Description page of Project Settings.

#include "DMC4Clone.h"
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

// Called when the game starts or when spawned
void ADMC4PlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    
}

// Called every frame
void ADMC4PlayerCharacter::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
}

// Called to bind functionality to input
void ADMC4PlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
    Super::SetupPlayerInputComponent(InputComponent);
    if(InputComponent)
    {
        InputComponent->BindAxis("RotateCamera", this, &ADMC4PlayerCharacter::RotateCamera);
        InputComponent->BindAxis("MoveForward", this, &ADMC4PlayerCharacter::MoveForward);
        InputComponent->BindAxis("MoveRight", this, &ADMC4PlayerCharacter::MoveRight);
    }
    else
    {
        UE_LOG(LogDMC, Warning, TEXT("Input Component is null in DMC4Character"));
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
