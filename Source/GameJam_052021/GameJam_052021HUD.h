// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameJam_052021HUD.generated.h"

UCLASS()
class AGameJam_052021HUD : public AHUD
{
	GENERATED_BODY()

public:
	AGameJam_052021HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

