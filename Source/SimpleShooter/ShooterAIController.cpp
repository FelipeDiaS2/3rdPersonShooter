// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "ShooterAIController.h"

// Called when the game starts or when spawned
void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	
    playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    aiPawn = GetPawn();

    //SetFocus(playerPawn);

    if(behaviorTree != nullptr)
    {
        RunBehaviorTree(behaviorTree);

        GetBlackboardComponent() -> SetValueAsVector(TEXT("InitialPosition"), aiPawn -> GetActorLocation());

    }

}

// Called every frame
void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    
    // if(LineOfSightTo(playerPawn))
    // {
    //     GetBlackboardComponent() -> SetValueAsVector(TEXT("PlayerLocation"), playerPawn -> GetActorLocation());

    //     GetBlackboardComponent() -> SetValueAsVector(TEXT("LastKnownPlayerPosition"), playerPawn -> GetActorLocation());

    // }
    // else 
    // {
    //    GetBlackboardComponent() -> ClearValue(TEXT("PlayerLocation"));
    // }

}