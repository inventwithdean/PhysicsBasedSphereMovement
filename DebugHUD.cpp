// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugHUD.h"
#include "Engine/Font.h"

ADebugHUD::ADebugHUD()
{
	static ConstructorHelpers::FObjectFinder<UFont> Font(TEXT("/Engine/EngineFonts/Roboto.Roboto"));
	MainFont = Font.Succeeded() ? Font.Object : nullptr;
}
