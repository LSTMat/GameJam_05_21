// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameJam_052021 : ModuleRules
{
	public GameJam_052021(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
