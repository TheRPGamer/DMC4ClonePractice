// Fill out your copyright notice in the Description page of Project Settings.

#include "DMC4Clone.h"
#include "DMC4Character.h"


// Sets default values
ADMC4Character::ADMC4Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    if(GetCapsuleComponent())
    {
        SetRootComponent(GetCapsuleComponent());
    }
    else
    {
        UE_LOG(LogDMC, Warning, TEXT("No Mesh On DMC4Character. Please attach a mesh."));
    }
    
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
        ThirdPersonSpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
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
    if(InputComponent)
    {
        InputComponent->BindAxis("RotateCamera", this, &ADMC4Character::RotateCamera);
        InputComponent->BindAxis("MoveForward", this, &ADMC4Character::MoveForward);
        InputComponent->BindAxis("MoveRight", this, &ADMC4Character::MoveRight);
    }
    else
    {
        UE_LOG(LogDMC, Warning, TEXT("Input Component is null in DMC4Character")); 
    }
}

void ADMC4Character::RotateCamera(float value)
{
    
    if(value)
    {
        AddControllerYawInput(value);
    }
}

void ADMC4Character::MoveForward(float value)
{
    if(value && ThirdPersonCamera)
    {
        FVector forward = ThirdPersonCamera->GetForwardVector();
        forward.Z=0;
        forward.Normalize();
        AddMovementInput(forward, value);
    }
}

void ADMC4Character::MoveRight(float value)
{
    if(value && ThirdPersonCamera)
    {
        FVector right = ThirdPersonCamera->GetRightVector();
        right.Z=0;
        right.Normalize();
        AddMovementInput(right, value);
    }
}