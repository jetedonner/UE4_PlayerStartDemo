//
//  PlayerStartCustomization.cpp
//  UE4_PlayerStartDemo
//
//  Created by Kim David Hauser on 22.03.22.
//  Copyright (c.) 2022 kimhauser.ch, DaVe Inc. (Kim David Hauser) - All rights reserved.
//

#include "PlayerStartCustomization.h"
#include "IDetailsView.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "DetailCategoryBuilder.h"
#include "Widgets/SNullWidget.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/SBoxPanel.h"
#include "Internationalization/Text.h"
#include "UObject/Class.h"
 
TSharedRef<IDetailCustomization> FPlayerStartCustomization::MakeInstance()
{
    return MakeShareable(new FPlayerStartCustomization);
}
 
void FPlayerStartCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
    //Edits a category. If it doesn't exist it creates a new one
    IDetailCategoryBuilder& CustomCategory = DetailBuilder.EditCategory("PlayerStart");
 
    //Store the currently selected objects from the viewport to the SelectedObjects array.
    DetailBuilder.GetObjectsBeingCustomized(SelectedObjects);
    
    PlayerStartProperty = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(APSWorldSettingsBase, DefaultPlayerStartTag), APSWorldSettingsBase::StaticClass());
    
    DetailBuilder.HideProperty(PlayerStartProperty);
    
    this->ReloadPlayerStarts();
    
    FString PlayerStartTagSetting;
    PlayerStartProperty->GetValue(PlayerStartTagSetting);
    
    TSharedPtr<FString> CurrentPlayerStartSharedRef;
    for(TSharedPtr<FString> item : ComboBoxOptions)
    {
        FString FSItem = *item;
        if(FSItem.Equals(PlayerStartTagSetting, ESearchCase::CaseSensitive))
        {
//            UE_LOG(LogTemp, Log, TEXT("PlayerStart Found and Selected: %s"), *PlayerStartTagSetting);
            CurrentPlayerStartSharedRef = item;
            break;
        }
    }
    
    CustomCategory.AddCustomRow(FText::FromString("PlayerStart"))
        .NameContent()
        [
            SNew(STextBlock).Text(FText::FromString("Player Start"))
            .Font(IDetailLayoutBuilder::GetDetailFont())
        ]
        .ValueContent()
        .VAlign(VAlign_Center)
        .MaxDesiredWidth(250)
        [
            SAssignNew(PlayerStartComboBox, STextComboBox)
            .Font(IDetailLayoutBuilder::GetDetailFont())
            .OptionsSource(&ComboBoxOptions)
            .InitiallySelectedItem(CurrentPlayerStartSharedRef)
            .OnSelectionChanged(this, &FPlayerStartCustomization::OnPlayerStartChanged)
        ];
    
    
    
    CustomCategory.AddCustomRow(FText::FromString("Goto actor in level"))
        .ValueContent()
        .VAlign(VAlign_Center)
        .MaxDesiredWidth(250)
        [
            SNew(SButton)
            .VAlign(VAlign_Center)
            .OnClicked(this, &FPlayerStartCustomization::ClickedOnButton)
            .Content()
            [
                SNew(STextBlock).Text(FText::FromString("GoTo PlayerStart"))
                .Font(IDetailLayoutBuilder::GetDetailFont())
            ]
        ];
    
    if (GEngine)
    {
//        UE_LOG(LogTemp, Log, TEXT("Setting up Actor-Delagates"));
        FDelegateHandle Handle = FEditorDelegates::OnNewActorsDropped.AddRaw(this, &FPlayerStartCustomization::OnNewActorsDropped);
        FDelegateHandle Handle2 = FEditorDelegates::OnDeleteActorsEnd.AddRaw(this, &FPlayerStartCustomization::OnDeleteActorsEnd);
    }
}

void FPlayerStartCustomization::OnNewActorsDropped(const TArray<UObject*>&, const TArray<AActor*>&)
{
//    GLog->Log("OnNewActorsDropped - CUSTOMIZATION!");
    
    TSharedPtr<FString> SelPlayerStart = PlayerStartComboBox->GetSelectedItem();
    
    this->ReloadPlayerStarts();
    
    this->ComboBoxSetToWorldProperty(SelPlayerStart);
}

void FPlayerStartCustomization::OnDeleteActorsEnd()
{
//    GLog->Log("OnDeleteActorsEnd - CUSTOMIZATION!");
    
    TSharedPtr<FString> SelPlayerStart = PlayerStartComboBox->GetSelectedItem();

    this->ReloadPlayerStarts();
    
    this->ComboBoxSetToWorldProperty(SelPlayerStart);
}

void FPlayerStartCustomization::ComboBoxSetToWorldProperty(TSharedPtr<FString> SelPlayerStart)
{
    FString PlayerStartTagSetting;
    PlayerStartProperty->GetValue(PlayerStartTagSetting);

    TSharedPtr<FString> DefaultItem;
    
    for(TSharedPtr<FString> item : ComboBoxOptions)
    {
        FString FSItem = *item;
        DefaultItem = item;
        if(FSItem.Equals(*SelPlayerStart, ESearchCase::CaseSensitive))
        {
//            UE_LOG(LogTemp, Log, TEXT("PlayerStart Found and Selected: %s - ADD"), *PlayerStartTagSetting);
            PlayerStartComboBox->SetSelectedItem(item);
            return;
        }
    }
    if(DefaultItem)
    {
        PlayerStartComboBox->SetSelectedItem(DefaultItem);
    }
}

void FPlayerStartCustomization::ReloadPlayerStarts()
{
//    GLog->Log("Reload PlayerStarts!");
    
    if(UWorld* World = GEditor->GetEditorWorldContext().World())
    {
        ComboBoxOptions.Empty();
        
        TArray<AActor*> ActorsToFind;
        UGameplayStatics::GetAllActorsOfClass(GEditor->GetEditorWorldContext().World(), APlayerStart::StaticClass(), ActorsToFind);
        
        for (AActor* PlayerStartActor: ActorsToFind)
        {
            APlayerStart* PlayerStartCast = Cast<APlayerStart>(PlayerStartActor);
            if (PlayerStartCast)
            {
//                UE_LOG(LogTemp, Log, TEXT("PlayerStart Found %s"), *PlayerStartCast->GetActorLabel());
                ComboBoxOptions.Add(MakeShared<FString>(FString(PlayerStartCast->GetActorLabel())));
            }
        }
    }
    if(PlayerStartComboBox)
    {
        PlayerStartComboBox->RefreshOptions();
    }
}

FReply FPlayerStartCustomization::ClickedOnButton()
{
//    GLog->Log("ViewPortCamera goto actor!");

    if (GEditor)
    {
        if(UWorld* World = GEditor->GetEditorWorldContext().World())
        {
            TArray<AActor*> ActorsToFind;
            UGameplayStatics::GetAllActorsOfClass(GEditor->GetEditorWorldContext().World(), APlayerStart::StaticClass(), ActorsToFind);
            
            for (AActor* PlayerStartActor: ActorsToFind)
            {
                APlayerStart* PlayerStartCast = Cast<APlayerStart>(PlayerStartActor);
                if (PlayerStartCast)
                {
//                    UE_LOG(LogTemp, Log, TEXT("PlayerStart Found %s"), *PlayerStartCast->GetActorLabel());
                    TSharedPtr<FString> PlayerStartSharedRef = MakeShared<FString>(FString(PlayerStartCast->GetActorLabel()));
                    
                    FString PlayerStartTagSetting;
                    PlayerStartProperty->GetValue(PlayerStartTagSetting);
                    
                    if(PlayerStartTagSetting.Equals(FString(PlayerStartCast->GetActorLabel())))
                    {
                        GEditor->MoveViewportCamerasToActor(*PlayerStartCast, true);
                        break;
                    }
                }
            }
        }
    }
    return FReply::Handled();
}

void FPlayerStartCustomization::OnPlayerStartChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo)
{
    if(NewValue)
    {
        PlayerStartProperty->SetValue(static_cast<FString>(*NewValue));
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("PlayerStart Selected: EMPTY!!"));
    }
}
