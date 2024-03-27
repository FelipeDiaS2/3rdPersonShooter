// Fill out your copyright notice in the Description page of Project Settings.


#include "GunActor.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"

#include "ShooterCharacter.h"


// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	rifle = GetWorld() -> SpawnActor<AGunActor>(rifleBlueprint);

	GetMesh() -> HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	rifle -> AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	rifle -> SetOwner(this);

	health = maxHealth;

	
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent -> BindAxis(TEXT("MoveForwardAndBackwards"), this, &AShooterCharacter::moveForwardAndBackwards);
	PlayerInputComponent -> BindAxis(TEXT("LookUpAndLookDown"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent -> BindAxis(TEXT("MoveRightAndLeft"), this, &AShooterCharacter::moveRightAndLeft);
	PlayerInputComponent -> BindAxis(TEXT("LookRightAndLookLeft"), this, &APawn::AddControllerYawInput);
	
	PlayerInputComponent -> BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent -> BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
}

void AShooterCharacter::moveForwardAndBackwards(float axisValue)
{
	AddMovementInput(GetActorForwardVector() *axisValue);
}

void AShooterCharacter::moveRightAndLeft(float axisValue)
{
	AddMovementInput(GetActorRightVector()* axisValue);
}

void AShooterCharacter::Shoot()
{

	rifle -> pullTheTrigger();

}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) 
{
	float damageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	damageToApply = FMath::Min(health, damageToApply);
	
	health -= damageToApply;
	

	if (isDead())
	{
		ASimpleShooterGameModeBase* gameMode = GetWorld() -> GetAuthGameMode<ASimpleShooterGameModeBase>();
		
		if(gameMode != nullptr)
		{
			gameMode -> PawnKilled(this);
		}

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent() -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return damageToApply;
}

bool AShooterCharacter::isDead() const
{
	if(health <= 0)
	{
		return true;
	}

	return false;

}

float AShooterCharacter::getPlayerHealthPercent() const
{
	
	return health / maxHealth;

}

