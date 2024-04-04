// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "BaseWall.generated.h"

UENUM(BlueprintType)
enum class UWallType : uint8
{
	Wood UMETA(DisplayName = "Wood Wall"),
	Cement UMETA(DisplayName = "Cement Wall"),
	ToughWall UMETA(DisplayName = "Tough Wall"),
	Steel UMETA(DisplayName = "Steel Wall")
};


UCLASS()
class CYBERTANKS_API ABaseWall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UWallType WallType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UGeometryCollectionComponent* GeometryCollection;

	UPROPERTY(EditAnywhere)
	FGameplayTag GameplayTag;

	UPROPERTY(EditAnywhere)
	FGameplayTag ProjectileGameplayTag;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFieldSystemActor> FieldSystemActor;

public:

	UFUNCTION(BlueprintCallable)
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
