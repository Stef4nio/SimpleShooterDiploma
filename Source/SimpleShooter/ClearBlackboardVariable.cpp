// Fill out your copyright notice in the Description page of Project Settings.


#include "ClearBlackboardVariable.h"

#include "BehaviorTree/BlackboardComponent.h"

UClearBlackboardVariable::UClearBlackboardVariable()
{
	NodeName = TEXT("ClearBlackboardVariable");
}

EBTNodeResult::Type UClearBlackboardVariable::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	return EBTNodeResult::Succeeded;
}
