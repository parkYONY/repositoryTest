// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestProjectCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Projectile.h"

ATestProjectCharacter::ATestProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	KeyCheck = false;
	fireOn = false;
	InputTime = 0.0f;
}
void ATestProjectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InputTime += DeltaTime;		
	if (KeyCheck)
	{		
		if (InputTime >= 3.0f)
		{
			fireOn = true;
		}
	}
	else
	{				
		if (fireOn)
		{
			Fire(fireOn);
			UE_LOG(LogTemp, Warning, TEXT("3second shoot"));
		}
		InputTime = 0.0f;
	}
}
//////////////////////////////////////////////////////////////////////////
// Input

void ATestProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATestProjectCharacter::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ATestProjectCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ATestProjectCharacter::TouchStopped);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATestProjectCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ATestProjectCharacter::StopFire);

	//PlayerInputComponent->BindAxis("FireBall", this, &ATestProjectCharacter::FireBall);
}

void ATestProjectCharacter::StartFire()
{
	KeyCheck = true;
}

void ATestProjectCharacter::StopFire()
{
	KeyCheck = false;
	if (!fireOn)
	{
		Fire(fireOn);
		UE_LOG(LogTemp, Warning, TEXT("basic shoot"));
	}	
}

void ATestProjectCharacter::MoveRight(float Value)
{
	// add movement in that direction	
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);	
}

void ATestProjectCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ATestProjectCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void ATestProjectCharacter::Fire(bool keycheck)
{	
	if (ProjectileClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fire"));		

		World = GetWorld();
		if (World != nullptr)
		{
			FVector playerLocation = World->GetFirstPlayerController()->GetPawn()->GetActorLocation();
			FRotator playerRotation = World->GetFirstPlayerController()->GetPawn()->GetActorRotation();
			
			FVector offset = FVector(20.0f, 0.0f, 0.0f);			
			FVector MuzzleLocation = playerLocation + FTransform(playerRotation).TransformVector(offset);
			MuzzleLocation.Z = (MuzzleLocation.Z / 2) + 50.0f;			
			FRotator MuzzleRotation = playerRotation;

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			TestProjectile = World->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

			if (TestProjectile != nullptr)
			{
				FVector LaunchDirection = MuzzleRotation.Vector();					
				TestProjectile->SetFireVelocitySetting(LaunchDirection);
				TestProjectile->SetArrowSetting(keycheck);
			}			
		}
		fireOn = false;
		InputTime = 0.0f;
	}
}

