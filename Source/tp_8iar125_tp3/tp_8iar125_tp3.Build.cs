// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class tp_8iar125_tp3 : ModuleRules
{
	public tp_8iar125_tp3(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
			{ "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "GameplayTasks", "AIModule", "NavigationSystem", "UMG",
				"TeamSystem"
			});
	}
}