// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestWorldSubsystem.h"

#include "QuestComponent.h"
#include "QuestDataAsset.h"



void UQuestWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	OnFirstStepFieldDelegate.AddDynamic(this, &UQuestWorldSubsystem::OnFirstStepField);

	// if (const UShepherdDeveloperSettings* Settings = GetDefault<UShepherdDeveloperSettings>())
	// {
	// 	QuestDataAsset = Settings->QuestDataAsset.LoadSynchronous();
	// }
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

void UQuestWorldSubsystem::OnFirstStepField(bool bArg)
{
	UQuestDataAsset** QuestData = QuestDataAsset->QuestMap.Find("GoSleep");

	if (QuestData != nullptr)
	{
		if (IsValid(*QuestData))
		{
			QuestComponent->StartQuest(*QuestData);
		}
	}
	
}

void UQuestWorldSubsystem::FirstStepFieldBroadcast(bool Value)
{
	OnFirstStepFieldDelegate.Broadcast(Value);
}

