// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestWorldSubsystem.h"

#include "QuestComponent.h"
#include "QuestDataAsset.h"
#include "QuestSystemDeveloperSettings.h"


void UQuestWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (const UQuestSystemDeveloperSettings* Settings = GetDefault<UQuestSystemDeveloperSettings>())
	{
		QuestDataAsset = Settings->QuestDataAsset.LoadSynchronous();
	}
}

void UQuestWorldSubsystem::Init()
{
	check (IsValid(QuestDataAsset))
	check (IsValid(QuestComponent))
	
	QuestComponent->ReadAllQuests(QuestDataAsset->QuestList);
}

void UQuestWorldSubsystem::RegisterComponent(UQuestComponent* InQuestComponent)
{
	QuestComponent = InQuestComponent;
}

void UQuestWorldSubsystem::BroadcastEvent(const FGameplayTag& EventTag)
{
	if (IsValid(QuestComponent))
	{
		QuestComponent->OnEventReceived(EventTag);
	}
}

