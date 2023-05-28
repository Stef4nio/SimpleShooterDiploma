// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FocusOnPlayer.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTTask_FocusOnPlayer : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FocusOnPlayer();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
