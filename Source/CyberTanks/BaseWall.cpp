// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWall.h"
#include "Field/FieldSystemActor.h"
//#include "Field/FieldSystemComponent.h"
//#include "Components/BoxComponent.h"
#include "Projectile.h"
//#include "GeometryCollection/GeometryCollectionComponent.h"


// Sets default values
ABaseWall::ABaseWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	// RootComponent = BoxComponent;

	// GeometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("Geometry Collection"));
	// GeometryCollection->SetupAttachment(RootComponent);

	//WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMesh"));
	//WallMesh->SetupAttachment(RootComponent);

	// FieldSystemComponent = CreateDefaultSubobject<UFieldSystemComponent>(TEXT("FieldSystemComponent"));
	// FieldSystemComponent->SetupAttachment(RootComponent);

	//FieldSystemComponent->ToggleVisibility();

	//FieldSystem = GetWorld()->SpawnActor<AFieldSystemActor>(AFieldSystemActor::StaticClass());
	// FieldSystem->SetActorLocation(GetActorLocation());
	// FieldSystem->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
}

void ABaseWall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit, FTransform HitTransform)
{
	UE_LOG(LogTemp, Display, TEXT("BaseWall Hit"));

	// auto MyOwner = GetOwner();
	// if (MyOwner == nullptr)
	// {
	// 	return;
	// }

	// auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	// auto DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor->IsA(AProjectile::StaticClass()))
	{
		AProjectile* Projectile = Cast<AProjectile>(OtherActor);
		UE_LOG(LogTemp, Display, TEXT("BaseWall Hit if %s, %s"), *Projectile->GameplayTag.ToString(), *ProjectileGameplayTag.ToString());
		if (Projectile->GameplayTag.MatchesTagExact(ProjectileGameplayTag))
		{
			UE_LOG(LogTemp, Display, TEXT("BaseWall Hit if if"));
			if (FieldSystemActor)
			{
				UE_LOG(LogTemp, Display, TEXT("spawn field system actor"));
				GetWorld()->SpawnActor<AFieldSystemActor>(FieldSystemActor, HitTransform);
			}
			// FieldSystemComponent->ToggleVisibility();
		}
	}
}

// Called when the game starts or when spawned
void ABaseWall::BeginPlay()
{
	Super::BeginPlay();
	//GeometryCollection->OnComponentHit.AddDynamic(this, &ABaseWall::OnHit);
}

// Called every frame
void ABaseWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

