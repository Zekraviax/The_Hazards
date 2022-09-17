// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheHazards : ModuleRules
{
	public TheHazards(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
        { "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "HeadMountedDisplay",
            "OnlineSubsystem",
            "OnlineSubsystemUtils",
        });

        DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");
    }
}