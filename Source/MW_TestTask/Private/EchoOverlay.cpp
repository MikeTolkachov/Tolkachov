// Fill out your copyright notice in the Description page of Project Settings.


#include "EchoOverlay.h"
#include "Components/TextBlock.h"

void UEchoOverlay::SetSouls(int32 Souls)
{
	if (SoulsCount)
	{
		const FString SoulsString = FString::Printf(TEXT("%d"), Souls);
		const FText SoulsText = FText::FromString(SoulsString);
		SoulsCount->SetText(SoulsText);
	}
}
