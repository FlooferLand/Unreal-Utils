using UnrealBuildTool;

public class Utility : ModuleRules
{
    public Utility(ReadOnlyTargetRules target) : base(target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        
        PublicDependencyModuleNames.AddRange(
            new[] { "Core", "CoreUObject", "Engine" }
        );

        PrivateDependencyModuleNames.AddRange(
            new[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "GameplayTasks"
            }
        );
    }
}