// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunActor.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGunActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunActor();

	void PullTrigger();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetMaxGunRange() const;

private:
	UPROPERTY(EditDefaultsOnly, Category="Gun Parameters")
	float MaxGunRange = 2000.f;
	UPROPERTY(EditDefaultsOnly, Category="Gun Parameters")
	float Damage = 10.f;
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* GunMesh;
	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* MuzzleFlashParticleSystem;
	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* ImpactParticleSystem;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* MuzzleSoundEffect;
	UPROPERTY(EditDefaultsOnly)
	USoundBase* ImpactSoundEffect;

	void GunTrace(FHitResult& hitResult, FVector& shotDirection);
	AController* GetOwnerController() const;
};
