// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PickupInterface.h"
#include "EchoCharacter.generated.h"


class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class ASoul;
class UEchoOverlay;
class UAttributeComponent;

UCLASS()
class MW_TESTTASK_API AEchoCharacter : public ACharacter, public IPickupInterface
{
	GENERATED_BODY()

public:
	AEchoCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Jump() override;
	virtual void SetOverlappingItem(ASoul* Soul) override;
	virtual void AddSouls(ASoul* Soul) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* EchoMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* EchoInputAction;

	UPROPERTY(EditAnywhere, Category = "Input");
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input");
	UInputAction* JumpAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAttributeComponent* Attributes;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

private: 
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleInstanceOnly)
	ASoul* OverlappingSoul;

	UPROPERTY()
	UEchoOverlay* EchoOverlay;

	void InitializeEchoOverlay(APlayerController* PlayerController);
};
