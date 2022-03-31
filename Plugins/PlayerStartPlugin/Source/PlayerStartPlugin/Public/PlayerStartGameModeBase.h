//
//  PlayerStartGameModeBase.h
//  UE4_PlayerStartDemo
//
//  Created by Kim David Hauser on 22.03.22.
//  Copyright (c.) 2022 kimhauser.ch, DaVe Inc. (Kim David Hauser) - All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "PSWorldSettingsBase.h"
#include "PlayerStartGameModeBase.generated.h"

/**
 
 */
UCLASS()
class PLAYERSTARTPLUGIN_API APlayerStartGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
    virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
};
