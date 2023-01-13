// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class OpenWorldRPG : ModuleRules
{
	public OpenWorldRPG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "HairStrandsCore", "GeometryCollectionEngine", "Niagara", "UMG", "AIModule" });
	}
}
