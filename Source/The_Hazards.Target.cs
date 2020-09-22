// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class The_HazardsTarget : TargetRules
{
	public The_HazardsTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

        //bUseLoggingInShipping = true;

		ExtraModuleNames.AddRange( new string[] { "The_Hazards" } );
	}
}
