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
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "PropertyCustomizationHelpers.h"

DEFINE_LOG_CATEGORY(DaVeLog);

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
            CurrentPlayerStartSharedRef = item;
            break;
        }
    }
    
    TSharedRef<SWidget> BrowseButton = PropertyCustomizationHelpers::MakeBrowseButton(FSimpleDelegate::CreateSP(this, &FPlayerStartCustomization::ClickedOnButtonNG), FText::FromString("Navigate to this PlayerStart in Viewport"));
    TSharedRef<SButton> BrowseButtonAsButton = StaticCastSharedRef<SButton>(BrowseButton);
    BrowseButtonAsButton->SetForegroundColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
    
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
             SNew(SHorizontalBox)
             +SHorizontalBox::Slot()
             .AutoWidth()
             .VAlign(VAlign_Center)
             .Padding(0, 0, 4, 0)
             [
                  SAssignNew(PlayerStartComboBox, STextComboBox)
                  .Font(IDetailLayoutBuilder::GetDetailFont())
                  .OptionsSource(&ComboBoxOptions)
                  .InitiallySelectedItem(CurrentPlayerStartSharedRef)
                  .OnSelectionChanged(this, &FPlayerStartCustomization::OnPlayerStartChanged)
             ]
             + SHorizontalBox::Slot()
             .AutoWidth()
             .VAlign(VAlign_Center)
             [
                BrowseButtonAsButton
             ]
        ];
    
    if (GEngine)
    {
        OnNewActorsDroppedHandle = FEditorDelegates::OnNewActorsDropped.AddRaw(this, &FPlayerStartCustomization::OnNewActorsDropped);
        OnDeleteActorsEndHandle = FEditorDelegates::OnDeleteActorsEnd.AddRaw(this, &FPlayerStartCustomization::OnDeleteActorsEnd);
    }
}

void FPlayerStartCustomization::OnNewActorsDropped(const TArray<UObject*>&, const TArray<AActor*>&)
{
    TSharedPtr<FString> SelPlayerStart = PlayerStartComboBox->GetSelectedItem();
    
    this->ReloadPlayerStarts();
    
    if(SelPlayerStart.IsValid())
    {
        this->ComboBoxSetToWorldProperty(SelPlayerStart);
    }
}

void FPlayerStartCustomization::OnDeleteActorsEnd()
{
    TSharedPtr<FString> SelPlayerStart = PlayerStartComboBox->GetSelectedItem();

    this->ReloadPlayerStarts();
    
    if(SelPlayerStart.IsValid())
    {
        this->ComboBoxSetToWorldProperty(SelPlayerStart);
    }
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
                ComboBoxOptions.Add(MakeShared<FString>(FString(PlayerStartCast->GetActorLabel())));
            }
        }
    }
    
    if(PlayerStartComboBox)
    {
        PlayerStartComboBox->RefreshOptions();
    }
}

void FPlayerStartCustomization::ClickedOnButtonNG()
{
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
}

void FPlayerStartCustomization::OnPlayerStartChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo)
{
    if(NewValue)
    {
        PlayerStartProperty->SetValue(static_cast<FString>(*NewValue));
    }
    else
    {
        UE_LOG(DaVeLog, Log, TEXT("PlayerStart Selected: EMPTY!!"));
    }
}

void FPlayerStartCustomization::PendingDelete()
{
    if (GEngine)
    {
        // handles below saved from AddRaw calls
        if (OnNewActorsDroppedHandle.IsValid())
        {
            FEditorDelegates::OnNewActorsDropped.Remove(OnNewActorsDroppedHandle);
            OnNewActorsDroppedHandle.Reset();
        }

        if (OnDeleteActorsEndHandle.IsValid())
        {
            FEditorDelegates::OnDeleteActorsEnd.Remove(OnDeleteActorsEndHandle);
            OnDeleteActorsEndHandle.Reset();
        }
    }
}
