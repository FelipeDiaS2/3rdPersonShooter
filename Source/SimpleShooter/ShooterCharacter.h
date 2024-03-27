// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintPure)
	bool isDead() const;

	UFUNCTION(BlueprintPure)
	float getPlayerHealthPercent() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Shoot();
	
private:


	void moveForwardAndBackwards(float axisValue);

	void moveRightAndLeft(float axisValue);

	UPROPERTY(EditDefaultsOnly, Category = "Blueprint Class")
	TSubclassOf<class AGunActor> rifleBlueprint;

	UPROPERTY()
	class AGunActor* rifle;

	UPROPERTY(VisibleAnywhere)
	float maxHealth = 100;

	UPROPERTY(EditDefaultsOnly)
	float health;

};
