// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FG_ProjectCharacter.generated.h"

UCLASS(config=Game)
class AFG_ProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	void StartAttackL(); // Light Button
	void StartAttackM(); // Medium Button
	void StartAttackH(); // Heavy Button
	void StartAttackS(); // Skill Button

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

	// Damage Function for Player
	void TakeDamage(int DamageAmount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health");
	int PlayerHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health");
	int PlayerMaxHealth;


public:
	AFG_ProjectCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};
