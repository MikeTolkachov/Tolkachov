// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = true;

	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
	RootComponent = PortalMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());

	PortalComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Embers"));
	PortalComponent->SetupAttachment(GetRootComponent());
}

void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void APortal::BeginPlay()
{
	Super::BeginPlay();	
}

