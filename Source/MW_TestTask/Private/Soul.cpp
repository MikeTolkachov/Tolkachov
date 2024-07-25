// Fill out your copyright notice in the Description page of Project Settings.


#include "Soul.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PickupInterface.h"
#include "EchoCharacter.h"

ASoul::ASoul()
{
	PrimaryActorTick.bCanEverTick = true;

	SoulMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SoulMeshComponent"));
	SoulMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SoulMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = SoulMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());

	SoulEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Embers"));
	SoulEffect->SetupAttachment(GetRootComponent());
}

void ASoul::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASoul::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ASoul::OnSphereOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ASoul::OnSphereEndOverlap);

}


void ASoul::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	if (PickupInterface)
	{
		PickupInterface->AddSouls(this);
	}
	SpawnPickupSound();
	Destroy();
}

void ASoul::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	if (PickupInterface)
	{
		PickupInterface->SetOverlappingItem(nullptr);
	}
}

void ASoul::SpawnPickupSound()
{
	if (PickupSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(
			this,
			PickupSound,
			GetActorLocation()
		);
	}
}


