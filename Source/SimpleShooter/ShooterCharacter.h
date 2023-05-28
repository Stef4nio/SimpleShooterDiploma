// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintCallable)
	void Fire();

	virtual void Jump() override;
	
	float GetShootingRange() const;
	
	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

private:
	UPROPERTY(EditAnywhere, Category="Movement")
	float turnRate = 10.f;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<class AGunActor> GunClass;

	UPROPERTY()
	AGunActor* Gun;

	UPROPERTY(EditDefaultsOnly, Category="Health")
	float MaxHealth = 100.f;
	UPROPERTY(VisibleAnywhere, Category="Health")
	float CurrentHealth = 0.f;
	
	void MoveForward(float axisValue);
	void MoveRight(float axisValue);
	
	void LookRight(float axisValue);
	void LookUp(float axisValue);

	void ControllerLookUp(float axisValue);
	void ControllerLookRight(float axisValue);
};


