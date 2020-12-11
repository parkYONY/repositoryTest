// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("aprojectile"));
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	if (CollisionComponent != nullptr)
	{		
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
		CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
		CollisionComponent->InitSphereRadius(15.0f);
		RootComponent = CollisionComponent;
	}

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	if (ProjectileMovementComponent != nullptr)
	{		
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
		ProjectileMovementComponent->InitialSpeed = 100.0f;
		ProjectileMovementComponent->MaxSpeed = 100.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;		
	}

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	if (ArrowComponent != nullptr)
	{		
		ArrowComponent->bHiddenInGame = false;
		ArrowComponent->ArrowColor = FColor(150, 200, 255);
		ArrowComponent->bTreatAsASprite = true;
		ArrowComponent->SetupAttachment(CollisionComponent);
		ArrowComponent->bIsScreenSizeScaled = true;			
		ArrowComponent->SetEditorScale(1.0f);
	}		
	destroyTime = 0;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();			
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);					
}
void AProjectile::SetFireVelocitySetting(const FVector& Direction)
{		
	//UE_LOG(LogTemp, Warning, TEXT("Velocity"));
	float velocityX = FMath::Clamp(Direction.X, -1.0f, 1.0f) * ProjectileMovementComponent->InitialSpeed;
	float velocityY = FMath::Clamp(Direction.Y, -1.0f, 1.0f) * ProjectileMovementComponent->InitialSpeed;
	float velocityZ = FMath::Clamp(Direction.Z, -1.0f, 1.0f) * ProjectileMovementComponent->InitialSpeed;

	FVector Veclocity = FVector(velocityX, velocityY, velocityZ);
	ProjectileMovementComponent->Velocity = Veclocity;	
}
void AProjectile::SetArrowSetting(bool type)
{	
	FVector scale = FVector(0.0f, 0.0f, 0.0f);
	destroyTime = 0;
	if (type)
	{
		destroyTime = 5;
		UE_LOG(LogTemp, Warning, TEXT("3second"));		
		scale = FVector(5.0f, 5.0f, 5.0f);						
	}
	else
	{		
		destroyTime = 3;
		UE_LOG(LogTemp, Warning, TEXT("basic"));		
		scale = FVector(1.0f, 1.0f, 1.0f);		
	}		
	ArrowComponent->SetWorldScale3D(scale);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AProjectile::TimeDestroy, 1.0f, true);
}
void AProjectile::TimeDestroy()
{	
	--destroyTime;
	if (destroyTime < 1)
	{
		ProjectileObjectDistroy();
	}
}
void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("collision"));
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{		
		ProjectileObjectDistroy();
		//OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}
}
void AProjectile::ProjectileObjectDistroy()
{
	CollisionComponent->DestroyComponent();
	ProjectileMovementComponent->DestroyComponent();
	ArrowComponent->DestroyComponent();
	this->Destroy();
}

