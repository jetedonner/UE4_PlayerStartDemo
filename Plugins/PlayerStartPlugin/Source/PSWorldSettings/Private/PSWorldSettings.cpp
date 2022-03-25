//
//  PSWorldSettings.cpp
//  UE4_PlayerStartDemo
//
//  Created by Kim David Hauser on 22.03.22.
//  Copyright (c.) 2022 kimhauser.ch, DaVe Inc. (Kim David Hauser) - All rights reserved.
//

#include "PSWorldSettings.h"

#define LOCTEXT_NAMESPACE "FPSWorldSettingsModule"

void FPSWorldSettingsModule::StartupModule()
{
    UE_LOG(LogTemp, Log, TEXT("FPSWorldSettingsModule module has started!"));
    DAVE_LOG_GENERAL;
}

void FPSWorldSettingsModule::ShutdownModule()
{
    UE_LOG(LogTemp, Log, TEXT("FPSWorldSettingsModule module has shutdown!"));
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FPSWorldSettingsModule, PSWorldSettings)
