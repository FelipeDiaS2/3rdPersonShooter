// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"
#include "Engine/DamageEvents.h"

#include "GunActor.h"

// Sets default values
AGunActor::AGunActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;

	staticMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	staticMeshComponent -> SetupAttachment(root);

}

// Called when the game starts or when spawned
void AGunActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunActor::pullTheTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(muzzleFlash, staticMeshComponent, TEXT("MuzzleFlashSocket"));	
	UGameplayStatics::SpawnSoundAttached(muzzleSound, staticMeshComponent, TEXT("MuzzleFlashSocket"));

	FHitResult outHit;
	FVector shotDirection;
	bool bSuccess = gunTrace(outHit, shotDirection);

	if(bSuccess)
	{
		//DrawDebugPoint(GetWorld(), outHit.Location, 20, FColor::Blue,true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitFlash, outHit.Location, shotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), hitMuzzleSound, outHit.Location);

		AActor* gotHit = outHit.GetActor();
		if (gotHit != nullptr)
		{
			FPointDamageEvent DamageEvent(damage, outHit, shotDirection, nullptr);
			AController* ownerController = getOwnerController();
			gotHit -> TakeDamage(damage, DamageEvent, ownerController, this);
		}

	}
}

bool AGunActor::gunTrace(FHitResult& outHit, FVector& ShotDirection)
{
	
	AController* ownerController = getOwnerController();
	if (ownerController == nullptr) return false;

	FVector outPosition;
	FRotator outRotation;
	ownerController -> GetPlayerViewPoint(outPosition, outRotation);
	
	ShotDirection = -outRotation.Vector();
		
	FVector endPoint = outPosition + outRotation.Vector() * maxRange;

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(GetOwner());

	return GetWorld() -> LineTraceSingleByChannel(outHit, outPosition, endPoint, ECollisionChannel::ECC_GameTraceChannel1, params);

}

AController* AGunActor::getOwnerController() const
{
	APawn* ownerPawn = Cast<APawn>(GetOwner());
	if (ownerPawn == nullptr) return nullptr;

	return ownerPawn -> GetController();
}

