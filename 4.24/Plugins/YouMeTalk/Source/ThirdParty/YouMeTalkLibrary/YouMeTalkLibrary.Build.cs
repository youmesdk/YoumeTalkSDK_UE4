// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class YouMeTalkLibrary : ModuleRules
{
	public YouMeTalkLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
                Path.Combine(ModuleDirectory, "include"),
            }
            );

        if (Target.Platform == UnrealTargetPlatform.Win32)
        {
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib/x86/youme_voice_engine.lib"));

            RuntimeDependencies.Add("$(BinaryOutputDir)/youme_voice_engine.dll", Path.Combine(ModuleDirectory, "lib/x86/youme_voice_engine.dll"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib/x86_64/youme_voice_engine.lib"));

            RuntimeDependencies.Add("$(BinaryOutputDir)/youme_voice_engine.dll", Path.Combine(ModuleDirectory, "lib/x86_64/youme_voice_engine.dll"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            string AndroidLibraryPath = Path.Combine(ModuleDirectory, "lib/android");

            PublicAdditionalLibraries.Add(Path.Combine(AndroidLibraryPath, "arm64-v8a", "libyoume_voice_engine.so"));


            PublicAdditionalLibraries.Add(Path.Combine(AndroidLibraryPath, "armeabi", "libyoume_voice_engine.so"));


            PublicAdditionalLibraries.Add(Path.Combine(AndroidLibraryPath, "armeabi-v7a", "libyoume_voice_engine.so"));


            PublicAdditionalLibraries.Add(Path.Combine(AndroidLibraryPath, "x86", "libyoume_voice_engine.so"));


            PublicAdditionalLibraries.Add(Path.Combine(AndroidLibraryPath, "x86_64", "libyoume_voice_engine.so"));

            PublicDependencyModuleNames.AddRange(new string[] { "Launch" });
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(AndroidLibraryPath, "YouMeTalk_UPL.xml"));
        }
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            PublicDefinitions.Add("YOUME_IOS");
            string VivoxLibraryPath = Path.Combine(ModuleDirectory, "lib/ios");

            PublicAdditionalLibraries.Add(Path.Combine(VivoxLibraryPath, "libyoume_voice_engine.a"));
            PublicAdditionalLibraries.Add(Path.Combine(VivoxLibraryPath, "libYouMeCommon.a"));
            PublicFrameworks.Add("CFNetwork");
            PublicFrameworks.Add("AVFoundation");
            PublicAdditionalLibraries.Add("sqlite3");
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicDefinitions.Add("YOUME_MAC");

            // PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "lib/Mac/Release", "libExampleLibrary.dylib"));
            // RuntimeDependencies.Add("$(PluginDir)/Source/ThirdParty/YoumiLibrary/Mac/Release/libExampleLibrary.dylib");
        }

        PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add other public dependencies that you statically link with here ...
                "Core",
                "Projects",
            }
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...	
                "CoreUObject",
                "Engine",
            }
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
    }
}
