// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FocusOnPlayer.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTask_FocusOnPlayer::UBTTask_FocusOnPlayer()
{
	NodeName = TEXT("Focus On Player");
}

EBTNodeResult::Type UBTTask_FocusOnPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	OwnerComp.GetAIOwner()->SetFocus(playerPawn);
	return EBTNodeResult::Succeeded;
}

