//
//  PlayerStartPlugin.cpp
//  UE4_PlayerStartDemo
//
//  Created by Kim David Hauser on 22.03.22.
//  Copyright (c.) 2022 kimhauser.ch, DaVe Inc. (Kim David Hauser) - All rights reserved.
//

#include "PlayerStartPlugin.h"

#define LOCTEXT_NAMESPACE "FPlayerStartPluginModule"

void FPlayerStartPluginModule::StartupModule()
{
     UE_LOG(LogTemp, Log, TEXT("FPlayerStartPluginModule module has started!"));
    
    FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    
    PropertyModule.RegisterCustomClassLayout(APSWorldSettingsBase::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FPlayerStartCustomization::MakeInstance));
    
    PropertyModule.NotifyCustomizationModuleChanged();
}

void FPlayerStartPluginModule::ShutdownModule()
{
    UE_LOG(LogTemp, Log, TEXT("FPlayerStartPluginModule module has shutdown!"));
    
    if(FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
    {
        auto& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

        PropertyModule.UnregisterCustomClassLayout(APSWorldSettingsBase::StaticClass()->GetFName());
        
        PropertyModule.NotifyCustomizationModuleChanged();
    }
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FPlayerStartPluginModule, PlayerStartPlugin)
