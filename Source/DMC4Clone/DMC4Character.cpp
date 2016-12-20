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

    ThirdPersonSpringArm->TargetArmLength = 250.0f;
    ThirdPersonSpringArm->bUsePawnControlRotation= true;
    ThirdPersonSpringArm->bAbsoluteRotation = false;
    ThirdPersonSpringArm->bInheritYaw = false;
    ThirdPersonSpringArm->SetupAttachment(RootComponent);
    
    
    ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>("ThirdPersonCamera");
    ThirdPersonCamera->SetProjectionMode(ECameraProjectionMode::Perspective)  ;
    ThirdPersonCamera->SetFieldOfView(120.0f);
    ThirdPersonCamera->SetupAttachment(ThirdPersonSpringArm, USpringArmComponent::SocketName);


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
    }
}

void ADMC4Character::RotateCamera(float value)
{
    
    if(Controller && value)
        AddControllerYawInput(value);
}
