// Some copyright should be here...

using UnrealBuildTool;

public class ASchmildosPlugin : ModuleRules
{
	public ASchmildosPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				

			}
			);
				
		//PublicIncludePaths.AddRange(new string[] { "$(PluginDir)/ThirdParty/USBLIB/public", "$(PluginDir)/ThirdParty/USBLIB/include" });
		PublicIncludePaths.AddRange(new string[] { "$(PluginDir)/ThirdParty/USBLIB/include" });
		PublicAdditionalLibraries.Add("$(PluginDir)/ThirdParty/USBLIB/libusb-1.0.lib");

		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
			OptimizeCode = CodeOptimization.Never;
	}
}
