//
//  PSGameModeBase.h
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
#include "PSGameModeBase.generated.h"

/**
 
 */
UCLASS()
class PSWORLDSETTINGS_API APSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
    virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
};
