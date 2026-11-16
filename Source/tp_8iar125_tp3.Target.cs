// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class tp_8iar125_tp3Target : TargetRules
{
	public tp_8iar125_tp3Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V7;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8;
		CppStandard = CppStandardVersion.Cpp20;
		ExtraModuleNames.Add("tp_8iar125_tp3");
		RegisterModulesCreatedByRider();
	}

	private void RegisterModulesCreatedByRider()
	{
		ExtraModuleNames.AddRange(new string[]
		{
			"TeamSystem",
		});
	}
}