// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GunActor.h"
#include "SimpleShooterGameModeBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->HideBoneByName(TEXT("weapon_r"), PBO_None);
	
	Gun = Cast<AGunActor>(GetWorld()->SpawnActor(GunClass));
	if(ensureAlwaysMsgf(Gun, TEXT("Something went wrong when spawning a gun for the character")))
	{
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		Gun->SetOwner(this);
	}

	CurrentHealth = MaxHealth;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AShooterCharacter::LookRight);
	PlayerInputComponent->BindAxis(TEXT("ControllerLookUp"), this, &AShooterCharacter::ControllerLookUp);
	PlayerInputComponent->BindAxis(TEXT("ControllerLookRight"), this, &AShooterCharacter::ControllerLookRight);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AShooterCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AShooterCharacter::Fire);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	const float DamageToReceive =  Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentHealth -= DamageToReceive;

	if(CurrentHealth <= 0)
	{
		CurrentHealth = 0;
	}

	if(IsDead())
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		ASimpleShooterGameModeBase* gameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();

		gameMode->PawnKilled(this);
		DetachFromControllerPendingDestroy();
	}
	
	UE_LOG(LogTemp, Warning, TEXT("%s health is now %f"), *GetName(), CurrentHealth);
	
	return DamageToReceive;
}

bool AShooterCharacter::IsDead() const
{
	return CurrentHealth <= 0;
}

void AShooterCharacter::MoveForward(float axisValue)
{
	AddMovementInput(GetActorForwardVector() * axisValue);
}

void AShooterCharacter::MoveRight(float axisValue)
{
	AddMovementInput(GetActorRightVector() * axisValue);
}

void AShooterCharacter::Jump()
{
	Super::Jump();
}

void AShooterCharacter::LookRight(float axisValue)
{
	AddControllerYawInput(axisValue);
}

void AShooterCharacter::LookUp(float axisValue)
{
	AddControllerPitchInput(axisValue);
}

void AShooterCharacter::ControllerLookUp(float axisValue)
{
	AddControllerPitchInput(axisValue * turnRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::ControllerLookRight(float axisValue)
{
	AddControllerYawInput(axisValue * turnRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Fire()
{
	Gun->PullTrigger();
}

float AShooterCharacter::GetShootingRange() const
{
	if(!Gun)
	{
		return -1.f;
	}

	return Gun->GetMaxGunRange();
}

float AShooterCharacter::GetHealthPercent() const
{
	return CurrentHealth/MaxHealth;
}

