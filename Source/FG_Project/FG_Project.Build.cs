// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FG_Project : ModuleRules
{
	public FG_Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
