// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	
	if(ensureAlwaysMsgf(behaviorTree, TEXT("Behaviour tree for AI %s is not set"), *GetName()))
	{
		RunBehaviorTree(behaviorTree);

		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

bool AShooterAIController::IsDead() const
{
	const AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(GetCharacter());
	
	if(ShooterCharacter)
	{
		return ShooterCharacter->IsDead();
	}
	
	return true;
}

