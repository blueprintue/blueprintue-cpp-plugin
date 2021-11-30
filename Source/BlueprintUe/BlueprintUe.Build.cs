using UnrealBuildTool;

public class BlueprintUe : ModuleRules
{
	public BlueprintUe(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[] {});
				
		PrivateIncludePaths.AddRange(new string[] {});
			
		PublicDependencyModuleNames.AddRange(new string[] {"Core", "UMG", "WebBrowser", "HTTP", "Json"});
			
		PrivateDependencyModuleNames.AddRange(new string[] {"Projects", "InputCore", "UnrealEd", "ToolMenus", "CoreUObject", "Engine", "Slate", "SlateCore"});
		
		DynamicallyLoadedModuleNames.AddRange(new string[] {});
	}
}
