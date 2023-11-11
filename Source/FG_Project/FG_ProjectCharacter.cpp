// Copyright Epic Games, Inc. All Rights Reserved.

#include "FG_ProjectCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AFG_ProjectCharacter::AFG_ProjectCharacter()
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

	PlayerMaxHealth = 1000;
	PlayerHealth = PlayerMaxHealth;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AFG_ProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFG_ProjectCharacter::MoveRight);

	PlayerInputComponent->BindAction("Light_Attack", IE_Pressed, this, &AFG_ProjectCharacter::StartAttackL);
	PlayerInputComponent->BindAction("Medium_Attack", IE_Pressed, this, &AFG_ProjectCharacter::StartAttackM);
	PlayerInputComponent->BindAction("Heavy_Attack", IE_Pressed, this, &AFG_ProjectCharacter::StartAttackH);
	PlayerInputComponent->BindAction("Skill_Attack", IE_Pressed, this, &AFG_ProjectCharacter::StartAttackS);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AFG_ProjectCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AFG_ProjectCharacter::TouchStopped);
}

void AFG_ProjectCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void AFG_ProjectCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void AFG_ProjectCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void AFG_ProjectCharacter::TakeDamage(int DamageAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("Player took %i damage points."), DamageAmount);
	PlayerHealth -= DamageAmount;

	if (PlayerHealth < 0) PlayerHealth = 0;
	UE_LOG(LogTemp, Warning, TEXT("Player has %i health remaining."), PlayerHealth);
}

void AFG_ProjectCharacter::StartAttackL()
{
	UE_LOG(LogTemp, Warning, TEXT("This is the Light Attack."));
	TakeDamage(100);
}

void AFG_ProjectCharacter::StartAttackM()
{
	UE_LOG(LogTemp, Warning, TEXT("This is the Medium Attack."));
	TakeDamage(200);
}

void AFG_ProjectCharacter::StartAttackH()
{
	UE_LOG(LogTemp, Warning, TEXT("This is the Heavy Attack."));
	TakeDamage(300);
}

void AFG_ProjectCharacter::StartAttackS()
{
	UE_LOG(LogTemp, Warning, TEXT("This is the Skill Attack."));
	TakeDamage(500);
}