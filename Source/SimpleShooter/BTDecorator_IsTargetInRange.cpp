// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsTargetInRange.h"

#include "AIController.h"
#include "ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBTDecorator_IsTargetInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                              uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	FVector targetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
	
	APawn* aiPawn = OwnerComp.GetAIOwner()->GetPawn();

	if(!aiPawn)
	{
		return false;
	}

	AShooterCharacter* aiCharacter = Cast<AShooterCharacter>(aiPawn);

	return FVector::DistSquared(targetLocation, aiPawn->GetActorLocation()) <= FMath::Square(aiCharacter->GetShootingRange());
	
}
