// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestComponent.h"

#include "ActiveQuestObject.h"
#include "QuestDataAsset.h"
#include "QuestObjective.h"
#include "QuestWorldSubsystem.h"

UQuestComponent::UQuestComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UQuestComponent::OnRegister()
{
    Super::OnRegister();

    if (UQuestWorldSubsystem* QuestWorldSubsystem = GetWorld()->GetSubsystem<UQuestWorldSubsystem>())
    {
        QuestWorldSubsystem->RegisterComponent(this);
        TArray<UQuestDataAsset*> dd;
        //QuestWorldSubsystem->QuestDataAsset->QuestMap.GenerateValueArray(dd);
        
    }
}

void UQuestComponent::StartQuest(UQuestDataAsset* NewQuest)
{
    if (!NewQuest) return;

    UActiveQuestObject* NewActiveQuest = NewObject<UActiveQuestObject>(this, UActiveQuestObject::StaticClass());
    NewActiveQuest->Quest = NewQuest;
    NewActiveQuest->Init(this);
    NewActiveQuest->OnActiveQuestFinished.AddDynamic(this,&UQuestComponent::OnActiveQuestFinished);
    
    ActivatedQuestList.Add(NewActiveQuest);

    if (const UQuestWorldSubsystem* QuestWorldSubsystem = GetWorld()->GetSubsystem<UQuestWorldSubsystem>())
    {
        QuestWorldSubsystem->OnQuestAddedDelegate.Broadcast(true);
    }
}


void UQuestComponent::OnEventReceived(const FGameplayTag& EventTag)
{
    for (UActiveQuestObject* Quest : ActivatedQuestList)
    {
        for (UQuestObjective* Objective : Quest->Objectives)
        {
            Objective->OnEventReceived(EventTag);
        }
    }
}

void UQuestComponent::OnActiveQuestFinished(UActiveQuestObject* ActiveQuest)
{
    ActiveQuest->OnActiveQuestFinished.RemoveDynamic(this,&UQuestComponent::OnActiveQuestFinished);
    ActiveQuest->Deinit();
    //ActivatedQuestList.Remove(ActiveQuest);

    if (const UQuestWorldSubsystem* QuestWorldSubsystem = GetWorld()->GetSubsystem<UQuestWorldSubsystem>())
    {
        QuestWorldSubsystem->OnQuestFinishDelegate.Broadcast(true);
    }
}
