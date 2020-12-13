// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestProjectCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Projectile.h"
#include "ProjectilUI.h"
#include "TestProjectGameMode.h"

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

	KeyCheckQ = false;
	KeyCheckW = false;

	fireOn = false;
	Isfire = false;		
	InputTime = 0.0f;
	GageTime = 0.0f;
	keyTpye = EFireType::E_END;		
}
void ATestProjectCharacter::BeginPlay()
{
	Super::BeginPlay();			
	ProjectilUIClass = NewObject<UProjectilUI>(UProjectilUI::StaticClass());
	if (ProjectilUIClass != nullptr)
	{
		ProjectilUIClass->Initailize();
	}
}
void ATestProjectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);		
	InputTime += DeltaTime;		
	if (KeyCheckQ)
	{						
		GageValue(input += DeltaTime);
		if (InputTime < 1.0f)
		{			
			if (KeyCheckW)
			{
				UE_LOG(LogTemp, Warning, TEXT("wPush"));
				keyTpye = EFireType::E_1Second_W;
				Fire(keyTpye);
				KeyCheckW = false;								
				Isfire = true;							
			}			
		}
		if (InputTime > 3.0f)
		{	
			UE_LOG(LogTemp, Warning, TEXT("3second"));				
			fireOn = true;			
		}			
	}
	else
	{
		InputTime = 0.0f;
		input = 0.0f;
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
	PlayerInputComponent->BindAction("FireSecond", IE_Pressed, this, &ATestProjectCharacter::StartFireSecond);
	PlayerInputComponent->BindAction("FireSecond", IE_Released, this, &ATestProjectCharacter::StopFireSecond);
}
void ATestProjectCharacter::StartFire()
{
	KeyCheckQ = true;			
	fireOn = false;		
	Isfire = false;
}
void ATestProjectCharacter::StopFire()
{	
	KeyCheckQ = false;
	if (!fireOn && !Isfire)
	{
		keyTpye = EFireType::E_Basic_Q;
		UE_LOG(LogTemp, Warning, TEXT("Qbasic"));
		Fire(keyTpye);
	}	
	else if(fireOn)
	{
		keyTpye = EFireType::E_3Second_Q;		
		Fire(keyTpye);
		fireOn = false;
	}	
}
void ATestProjectCharacter::StartFireSecond()
{		
	KeyCheckW = true;		
	Isfire = false;
}
void ATestProjectCharacter::StopFireSecond()
{		
	KeyCheckW = false;		
	if (!Isfire && !fireOn)
	{
		keyTpye = EFireType::E_Basic_W;
		UE_LOG(LogTemp, Warning, TEXT("Wbasic"));
		Fire(keyTpye);				
		InputTime = 0.0f;		
	}
	GageTime = 0.0f;
}
void ATestProjectCharacter::GageValue(float value)
{
	GageTime = value;
	if (GageTime < 1)
	{
		GageTime = 0.0f;
	}
	if (GageTime > 3.0f)
	{
		GageTime = 3.0f;
	}	
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Input Value : Float : %f"), (GageTime / 3.0f)));
	//if (ProjectilUIClass)
	//{
	//	ProjectilUIClass->SetGage(GageTime, 3.0f);
	//}
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
void ATestProjectCharacter::Fire(/*bool keycheck*/ EFireType keytype)
{	
	if (ProjectileClass)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Fire"));		

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
			//TestProjectile->CreateObject(World, MuzzleLocation, MuzzleRotation);
			if (TestProjectile != nullptr)
			{
				FVector LaunchDirection = MuzzleRotation.Vector();					
				TestProjectile->SetFireVelocitySetting(LaunchDirection);

				switch (keytype)
				{
				case EFireType::E_3Second_Q:
					TestProjectile->SetArrowSetting(FVector(5.0f,5.0f,5.0f), FColor(255,0,0));
					TestProjectile->TimeDestroy(5);
					break;
				case EFireType::E_Basic_Q:					
					TestProjectile->TimeDestroy(3);
					break;
				case EFireType::E_1Second_W:				
					TestProjectile->SetArrowSetting(FVector(1.0f,1.0f,1.0f), FColor(0, 0, 255));
					TestProjectile->TimeDestroy(3);
					break;
				case EFireType::E_Basic_W:											
					TestProjectile->TimeDestroy(5);
					break;
				default:
					break;
				}
			}			
		}		
	}
}

