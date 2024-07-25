// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EchoOverlay.generated.h"

/**
 * 
 */
UCLASS()
class MW_TESTTASK_API UEchoOverlay : public UUserWidget
{
	GENERATED_BODY()

public: 

	void SetSouls(int32 Souls);

private: 
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SoulsCount;
};
