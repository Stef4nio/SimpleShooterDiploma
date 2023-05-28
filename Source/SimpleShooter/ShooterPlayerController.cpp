// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

#include "ShooterCharacter.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	HUDHandle->RemoveFromViewport();
	
	if(!bIsWinner)
	{
		UUserWidget* loseScreen = CreateWidget(this, LoseScreenWidget, TEXT("LoseScreenWidget"));
		if(ensureAlwaysMsgf(loseScreen, TEXT("%s couldn't create a lose screen widget"), *GetPawn()->GetName()))
		{
			loseScreen->AddToViewport();
		}
	}
	else
	{
		UUserWidget* winScreen = CreateWidget(this, WinScreenWidget, TEXT("WinScreenWidget"));
		if(ensureAlwaysMsgf(winScreen, TEXT("%s couldn't create a lose screen widget"), *GetPawn()->GetName()))
		{
			winScreen->AddToViewport();
		}
	}

	GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &AShooterPlayerController::RestartLevel, RestartDelay);
}

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();
	HUDHandle = CreateWidget(this, HUD, TEXT("GUD"));
	if(ensureAlwaysMsgf(HUDHandle, TEXT("%s couldn't create a HUD widget"), *GetPawn()->GetName()))
	{
		HUDHandle->AddToViewport();
	}
}

