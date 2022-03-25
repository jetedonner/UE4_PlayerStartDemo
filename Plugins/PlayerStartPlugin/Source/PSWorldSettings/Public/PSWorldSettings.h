//
//  PSWorldSettings.h
//  UE4_PlayerStartDemo
//
//  Created by Kim David Hauser on 22.03.22.
//  Copyright (c.) 2022 kimhauser.ch, DaVe Inc. (Kim David Hauser) - All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Engine/Engine.h"
#include "GlobalDefinitions.h"

class FPSWorldSettingsModule : public IModuleInterface
{
public:

    /* IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

};
