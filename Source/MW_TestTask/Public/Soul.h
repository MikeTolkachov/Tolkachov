// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Soul.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
class USphereComponent;

UCLASS()
class MW_TESTTASK_API ASoul : public AActor
{
	GENERATED_BODY()
	
public:	
	ASoul();
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SpawnPickupSound();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* SoulMesh;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* SoulEffect;

	UPROPERTY(EditAnywhere)
	USoundBase* PickupSound;

private:

	UPROPERTY(EditAnywhere, Category = "Soul Properties")
	int32 Souls;


public:
	FORCEINLINE int32 GetSouls() const { return Souls; }
	FORCEINLINE void SetSouls(int32 NumberOfSouls) { Souls = NumberOfSouls; }
};
