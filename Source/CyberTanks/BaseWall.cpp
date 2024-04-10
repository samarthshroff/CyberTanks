// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWall.h"
#include "Field/FieldSystemActor.h"
//#include "Field/FieldSystemComponent.h"
//#include "Components/BoxComponent.h"
#include "Projectile.h"
#include "GeometryCollection/GeometryCollectionComponent.h"


// Sets default values
ABaseWall::ABaseWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GeometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("Geometry Collection"));
	RootComponent = GeometryCollection;

}

void ABaseWall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor->IsA(AProjectile::StaticClass()))
	{
		AProjectile* Projectile = Cast<AProjectile>(OtherActor);
		if (Projectile->GameplayTag.MatchesTagExact(ProjectileGameplayTag))
		{
			if (FieldSystemActor)
			{
				DrawDebugSphere(GetWorld(), GetActorLocation(), 25.f, 12, FColor::Red, false, 3.f);

				GetWorld()->SpawnActor<AFieldSystemActor>(FieldSystemActor, GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f));
			}
		}
	}
}

// Called when the game starts or when spawned
void ABaseWall::BeginPlay()
{
	Super::BeginPlay();
	GeometryCollection->OnComponentHit.AddDynamic(this, &ABaseWall::OnHit);
}
