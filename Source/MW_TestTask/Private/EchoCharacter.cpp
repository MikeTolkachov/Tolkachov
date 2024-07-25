// Fill out your copyright notice in the Description page of Project Settings.


#include "EchoCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "AttributeComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Soul.h"
#include "EchoHUD.h"
#include "EchoOverlay.h"

AEchoCharacter::AEchoCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 200.f, 0.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);

	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attributes"));
}

void AEchoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEchoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(EchoInputAction, ETriggerEvent::Triggered, this, &AEchoCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AEchoCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AEchoCharacter::Jump);
	}

}

void AEchoCharacter::Jump()
{
	Super::Jump();
}

void AEchoCharacter::SetOverlappingItem(ASoul* Soul)
{
	OverlappingSoul = Soul;
}

void AEchoCharacter::AddSouls(ASoul* Soul)
{
	if (Attributes && EchoOverlay)
	{
		Attributes->AddSouls(Soul->GetSouls());
		EchoOverlay->SetSouls(Attributes->GetSouls());
	}
}

void AEchoCharacter::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(EchoMappingContext, 0);
		}

		InitializeEchoOverlay(PlayerController);
	}

}

void AEchoCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void AEchoCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

void AEchoCharacter::InitializeEchoOverlay(APlayerController* PlayerController)
{
	AEchoHUD* EchoHUD = Cast<AEchoHUD>(PlayerController->GetHUD());
	if (EchoHUD)
	{
		EchoOverlay = EchoHUD->GetEchoOverlay();
		if (EchoOverlay)
		{
			EchoOverlay->SetSouls(0);
		}
	}
}