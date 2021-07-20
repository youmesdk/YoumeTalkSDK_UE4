// Copyright © 2014-2021 YouMe. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FYouMeTalkModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
