//
//  PlayerStartGameModeBase.cpp
//  UE4_PlayerStartDemo
//
//  Created by Kim David Hauser on 22.03.22.
//  Copyright (c.) 2022 kimhauser.ch, DaVe Inc. (Kim David Hauser) - All rights reserved.
//

#include "PlayerStartGameModeBase.h"

AActor* APlayerStartGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
    if(Player)
    {
        UWorld* World = Player->GetWorld();
        if(World)
        {
            APSWorldSettingsBase* PlayerStartWorldSettings = Cast<APSWorldSettingsBase>(World->GetWorldSettings());
            if(PlayerStartWorldSettings)
            {
                TArray<AActor*> ActorsToFind;
                UGameplayStatics::GetAllActorsOfClass(World, APlayerStart::StaticClass(), ActorsToFind);
                
                for (AActor* PlayerStartActor: ActorsToFind)
                {
                    APlayerStart* PlayerStartCast = Cast<APlayerStart>(PlayerStartActor);
                    if (PlayerStartCast)
                    {
                        TSharedPtr<FString> PlayerStartSharedRef = MakeShared<FString>(FString(PlayerStartCast->GetActorLabel()));
                        
                        FString PlayerStartTagSetting = PlayerStartWorldSettings->DefaultPlayerStartTag;
                        if(PlayerStartTagSetting.Equals(FString(PlayerStartCast->GetActorLabel())))
                        {
                            return PlayerStartCast;
                        }
                    }
                }
            }
            else
            {
                UE_LOG(LogTemp, Log, TEXT("APlayerStartGameModeBase::ChoosePlayerStart_Implenentation => PlayerStartWorldSettings IS NULL (Couldnt be casted)!"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("APlayerStartGameModeBase::ChoosePlayerStart_Implenentation => World IS NULL!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("APlayerStartGameModeBase::ChoosePlayerStart_Implenentation => Player IS NULL!"));
    }
    return NULL;
}
