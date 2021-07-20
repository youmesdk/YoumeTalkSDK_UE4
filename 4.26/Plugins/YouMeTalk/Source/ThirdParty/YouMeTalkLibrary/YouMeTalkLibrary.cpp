﻿// Copyright © 2014-2021 YouMe. All Rights Reserved.

#include "YouMeTalkLibrary.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FYouMeTalkLibrary"

void FYouMeTalkLibrary::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FYouMeTalkLibrary::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FYouMeTalkLibrary, YouMeTalkLibrary)
