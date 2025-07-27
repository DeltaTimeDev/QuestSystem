// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest.h"

#include "QuestComponent.h"
#include "QuestDataAsset.h"
#include "QuestObjective.h"

void UQuest::Init(UQuestComponent* InQuestComponent)
{
	QuestComponent = InQuestComponent;
	for (TSubclassOf<UQuestObjective> ObjClass : QuestDataAsset->Objectives)
	{
		if (ObjClass)
		{
			UQuestObjective* Obj = NewObject<UQuestObjective>(QuestComponent, ObjClass);
			Obj->ActivateObjective(QuestComponent->GetOwner());
			Obj->OnCompleted.AddDynamic(this, &UQuest::OnObjectiveCompleted);
			Objectives.Add(Obj);
		}
	}
}

void UQuest::Deinit()
{
}

void UQuest::OnObjectiveCompleted(UQuestObjective* Objective)
{
	bool AllCompleted = true;
	for (UQuestObjective* Objective : Objectives)
	{
		if (!Objective->bIsCompleted)
		{
			AllCompleted = false;
			break;
		}
	}

	if (AllCompleted)
	{
		bIsCompleted = true;
		OnQuestFinished.Broadcast(this);
	}
}

FString UQuest::GetQuestName()
{
	if (QuestDataAsset)
	{
		return QuestDataAsset->QuestName;
	}
	return FString();
}

void UQuest::OnEventReceived(const FGameplayTag& EventTag)
{
	if (EventTag.MatchesTagExact(QuestDataAsset->ActivateQuestEvent))
	{
		QuestComponent->ActivateQuest(this);
	}

	if (QuestDataAsset->ActivateQuestNameAfterFinish != "")
	{
		QuestComponent->ActivateQuest(QuestDataAsset->ActivateQuestNameAfterFinish);
	}
}
