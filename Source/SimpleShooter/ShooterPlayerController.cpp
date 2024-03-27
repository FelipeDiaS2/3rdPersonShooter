// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

    crosshairWidget = CreateWidget(this, crosshairClass);
    if (crosshairWidget != nullptr)
    {
        crosshairWidget -> AddToViewport();
    }


}

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    crosshairWidget -> RemoveFromViewport();

    UUserWidget* looseScreenWidget = CreateWidget(this, looseScreenClass);
    if (looseScreenWidget != nullptr) 
    {
        looseScreenWidget -> AddToViewport();
    }


    GetWorldTimerManager().SetTimer(timerHandle, this, &APlayerController::RestartLevel, restartDelay);

}

