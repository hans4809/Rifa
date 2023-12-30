// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Rifa : ModuleRules
{
	public Rifa(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "UMG", "AIModule", "GameplayTasks", "Niagara", "MovieScene", "LevelSequence" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
    }
}
