// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunActor.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGunActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void pullTheTrigger();

private:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* root;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* staticMeshComponent;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* muzzleFlash;

	UPROPERTY(EditAnywhere)
	class USoundBase* muzzleSound;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* hitFlash;

	UPROPERTY(EditAnywhere)
	class USoundBase* hitMuzzleSound;

	UPROPERTY(EditAnywhere)
	float maxRange = 10000;

	UPROPERTY(EditAnywhere)
	float damage = 10;

	bool gunTrace(FHitResult& Hit, FVector& ShotDirection);

	AController* getOwnerController() const;

};
