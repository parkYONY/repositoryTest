// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestProjectCharacter.generated.h"

UENUM()
enum class EFireType : uint8
{
	E_1Second_W UMETA(DisplayName = "1Second W"),
	E_3Second_Q UMETA(DisplayName = "3Second Q"),
	E_Basic_Q UMETA(DisplayName = "Basic Q"),
	E_Basic_W UMETA(DisplayName = "Basic W"),
	E_END	  UMETA(DisplayName = "END"),
};

UCLASS(config=Game)
class ATestProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


public:
	ATestProjectCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

public:

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(VisibleAnywhere)
	class AProjectile* TestProjectile;

	UPROPERTY(VisibleAnywhere)
	class UProjectilUI* ProjectilUIClass;

	UWorld* World;
	bool KeyCheckQ;
	bool KeyCheckW;

	bool fireOn;	
	bool Isfire;		
	float InputTime;	
	EFireType keyTpye;
	float GageTime;
	float input;

public:
	UFUNCTION()		
	void Fire(/*bool keycheck*/EFireType keytype);

	UFUNCTION()
	void GageValue(float value);
	float GetGageData();

	void StartFire();
	void StopFire();	
	void StartFireSecond();
	void StopFireSecond();	
	
};
