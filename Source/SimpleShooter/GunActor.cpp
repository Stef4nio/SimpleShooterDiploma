// Fill out your copyright notice in the Description page of Project Settings.

#define OUT

#include "GunActor.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AGunActor::AGunActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun's Mesh"));
	GunMesh->SetupAttachment(Root);

}

void AGunActor::PullTrigger()
{
	FHitResult lineTraceResult;
	FVector shotDirection;
	GunTrace(OUT lineTraceResult, OUT shotDirection);
	
	if(lineTraceResult.bBlockingHit)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSoundEffect, lineTraceResult.Location, shotDirection.Rotation());

		if(AActor* damagedActor = lineTraceResult.GetActor())
		{
			FPointDamageEvent damageEvent{Damage, lineTraceResult, shotDirection, nullptr};

			damagedActor->TakeDamage(Damage, damageEvent, GetOwnerController(), this);
		}
		
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactParticleSystem, lineTraceResult.Location, shotDirection.Rotation());
	}

	UGameplayStatics::SpawnEmitterAttached(MuzzleFlashParticleSystem, GunMesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSoundEffect, GunMesh, TEXT("MuzzleFlashSocket"));
}

// Called when the game starts or when spawned
void AGunActor::BeginPlay()
{
	Super::BeginPlay();

	ensureAlwaysMsgf(MuzzleFlashParticleSystem, TEXT("Muzzle Flash Particle System isn't setup for a gun actor %s"), *GetName());
	ensureAlwaysMsgf(ImpactParticleSystem, TEXT("Impact Particle System isn't setup for a gun actor %s"), *GetName());
	ensureAlwaysMsgf(MuzzleSoundEffect, TEXT("Muzzle Sound Effect isn't setup for a gun actor %s"), *GetName());
	ensureAlwaysMsgf(ImpactSoundEffect, TEXT("Impact Sound Effect isn't setup for a gun actor %s"), *GetName());
}

// Called every frame
void AGunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AGunActor::GetMaxGunRange() const
{
	return MaxGunRange;
}

void AGunActor::GunTrace(FHitResult& hitResult, FVector& shotDirection)
{
	AController* ownerController = GetOwnerController();
	if(!ownerController)
	{
		return;
	}

	FVector viewpointLocation;
	FRotator viewpointRotation;
	ownerController->GetPlayerViewPoint(OUT viewpointLocation, OUT viewpointRotation);

	FVector lineTraceEnd = viewpointLocation + viewpointRotation.Vector() * MaxGunRange;
	
	FCollisionQueryParams lineTraceParams;
	lineTraceParams.AddIgnoredActor(this);
	lineTraceParams.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(OUT hitResult, viewpointLocation, lineTraceEnd, ECC_GameTraceChannel1, lineTraceParams);

	shotDirection = -viewpointRotation.Vector();
}

AController* AGunActor::GetOwnerController() const
{
	APawn* owner = Cast<APawn>(GetOwner());
	if(!owner)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't obtain an owner of the gun %s"), *GetName());
		return nullptr;
	}
	AController* ownerController = owner->GetController();
	if(!ownerController)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't obtain a controller of the owner pawn %s of the gun %s"),*owner->GetName(),
			*GetName());
		return nullptr;
	}

	return ownerController;
}

