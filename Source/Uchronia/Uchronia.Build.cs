// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Uchronia : ModuleRules
{
	public Uchronia(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayAbilities", "UMG", "PhysicsCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Niagara", "GameplayTags", "GameplayTasks", "AIModule", "Slate", "SlateCore", "EnhancedInput" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
