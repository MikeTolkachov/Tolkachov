// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

class UNiagaraComponent;
class USphereComponent;

UCLASS()
class MW_TESTTASK_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	

	APortal();
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* PortalMesh;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UNiagaraComponent* PortalComponent;

};
