// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectTileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectTileSpawnPoint->SetupAttachment(TurretMesh);

	IsFiring = false;
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtLocation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), LookAtLocation, UGameplayStatics::GetWorldDeltaSeconds(this), 25.f));
}

// TODO - Add argument for weaponIndex that corresponds to the weapons from gameplaytag
void ABasePawn::Fire()
{

	//UE_LOG(LogTemp, Display, TEXT("The gameplay tag is %s and rate of fire is %d"), *(CurrentProjectile.ToString()), NumberOfBulletsPerClick[CurrentProjectile]);

	UE_LOG(LogTemp, Display, TEXT("The gameplay tag is %s and rate of fire is %d"), *(CurrentProjectile.ToString()), ProjectileData[CurrentProjectile].NumberOfBullets);
	// TODO - add an if to set this value after a delay of reload and cooldown
	PendingProjectileToFire += ProjectileData[CurrentProjectile].NumberOfBullets;

	if (!IsFiring)
	{
		UE_LOG(LogTemp, Display, TEXT("in IsFiring"));
		IsFiring = true;

		GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ABasePawn::FireProjectile, ProjectileData[CurrentProjectile].Interval, true);
	}
	//DrawDebugSphere(GetWorld(), Location, 25.f, 12, FColor::Red, false, 3.f);
	/*if (!IsFiring)
	{
		IsFiring = true;
		FVector Location = ProjectTileSpawnPoint->GetComponentLocation();
		FRotator Rotation = ProjectTileSpawnPoint->GetComponentRotation();
		int RateOfFire = NumberOfBulletsPerClick[CurrentProjectile];
		for (auto i = 0;i < RateOfFire;++i)
		{
			AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
			Projectile->SetOwner(this);
		}
		IsFiring = false;
	}*/
}

void ABasePawn::FireProjectile()
{
	UE_LOG(LogTemp, Display, TEXT("FireProjectile"));
	FVector Location = ProjectTileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectTileSpawnPoint->GetComponentRotation();
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);

	UE_LOG(LogTemp, Display, TEXT("Pending projectiles before %d"), PendingProjectileToFire);
	--PendingProjectileToFire;
	UE_LOG(LogTemp, Display, TEXT("Pending projectiles after %d"), PendingProjectileToFire);
	if (PendingProjectileToFire <= 0)
	{
		UE_LOG(LogTemp, Display, TEXT("No more Pending projectiles"));
		GetWorldTimerManager().ClearTimer(FireRateTimerHandle);
		IsFiring = false;
	}

}

void ABasePawn::HandleDestruction()
{
	if (DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	}
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
	if (DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}