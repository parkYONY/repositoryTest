// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TESTPROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(VisibleAnywhere, Category = Arrow)
	class UArrowComponent* ArrowComponent;	

	FTimerHandle TimerHandle;		
	int32 destroyTime;	
	FColor colorSetting;

public:
	void SetFireVelocitySetting(const FVector& Direction);	
	
	UFUNCTION()
	void SetArrowSetting(FVector scale, FColor color);
	
	void TimeDestroy(int32 destroytime);
	void TimeDestroy();
	void ProjectileObjectDistroy();	
	void CreateObject(UWorld* World, FVector Location, FRotator Rotation);
};
