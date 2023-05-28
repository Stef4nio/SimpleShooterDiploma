// Fill out your copyright notice in the Description page of Project Settings.


#include "KilllThemAllGameMode.h"

#include "EngineUtils.h"
#include "ShooterAIController.h"

void AKilllThemAllGameMode::PawnKilled(APawn* killedPawn)
{
	Super::PawnKilled(killedPawn);



	if(const AController* killedPawnController = killedPawn->GetController())
	{
		if(killedPawnController->IsPlayerController())
		{
			EndGame(false);
			return;
		}
	}
	
	for(AShooterAIController* enemyController : TActorRange<AShooterAIController>(GetWorld()))
	{
		if(!enemyController->IsDead())
		{
			return;
		}
	}
	

	EndGame(true);
}

void AKilllThemAllGameMode::EndGame(bool isPlayerWon)
{
	for(AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool isWinner = Controller->IsPlayerController() && isPlayerWon;
		Controller->GameHasEnded(Controller->GetPawn(), isPlayerWon);
	}
}
