//
//  PSWorldSettingsBase.cpp
//  UE4_PlayerStartDemo
//
//  Created by Kim David Hauser on 22.03.22.
//  Copyright (c.) 2022 kimhauser.ch, DaVe Inc. (Kim David Hauser) - All rights reserved.
//

#include "PSWorldSettingsBase.h"
#include "PSGameModeBase.h"

DEFINE_LOG_CATEGORY(DaVeLog);

APSWorldSettingsBase::APSWorldSettingsBase():Super()
{
    this->DefaultGameMode = APSGameModeBase::StaticClass();
}

APSWorldSettingsBase::APSWorldSettingsBase(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
    this->DefaultGameMode = APSGameModeBase::StaticClass();
}

void APSWorldSettingsBase::BeginPlay()
{
    Super::BeginPlay();
}
