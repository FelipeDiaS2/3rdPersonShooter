// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"


UBTTaskNode_Shoot::UBTTaskNode_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if (OwnerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AShooterCharacter* character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner() -> GetPawn());
    if(character == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    character -> Shoot();

    return EBTNodeResult::Succeeded;

}

