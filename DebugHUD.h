// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"

#include "DebugHUD.generated.h"

/**
 * 
 */
UCLASS()
class ADebugHUD : public AHUD
{
	GENERATED_BODY()
protected:
	ADebugHUD();

	void AddText(const TCHAR* Title, const FText& Value)
	{
		RenderStatistic(Title, Value);
	}

	void AddFloat(const TCHAR* Title, float Value)
	{
		RenderStatistic(Title, FText::AsNumber(Value));
	}

	void AddInt(const TCHAR* Title, int32 Value)
	{
		RenderStatistic(Title, FText::AsNumber(Value));
	}

	void AddBool(const TCHAR* Title, bool Value)
	{
		RenderStatistic(Title, BoolToText(Value), (Value == false) ? FLinearColor::Red : FLinearColor::Green);
	}

	virtual void DrawHUD() override
	{
		X = Y = 50.f;
	}

	float HorizontalOffset = 150.f;
private:
	UPROPERTY(Transient)
	class UFont* MainFont;

	FText CStringToText(const TCHAR* Text)
	{
		return FText::FromString(Text);
	}

	FText BoolToText(bool Value)
	{
		return CStringToText((Value == true) ? TEXT("true") : TEXT("false"));
	}

	void RenderStatistic(const TCHAR* Title, const FText& Value, const FLinearColor& ValueColor = FLinearColor::White)
	{
		FCanvasTextItem Item00(FVector2D(X, Y), CStringToText(Title), MainFont, FLinearColor::White);
		Canvas->DrawItem(Item00);
		FCanvasTextItem Item01(FVector2D(X + HorizontalOffset, Y), Value, MainFont, ValueColor);
		Canvas->DrawItem(Item01);
		Y += LineHeight;
	}

	float X = 50.f;
	float Y = 50.f;
	float LineHeight = 16.0f;
};
