// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public: 

	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	float restartDelay = 5.f;

	FTimerHandle timerHandle;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> looseScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> crosshairClass;

	UUserWidget* crosshairWidget;

};
