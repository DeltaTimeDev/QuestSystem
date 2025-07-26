// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveQuestObject.h"

#include "QuestComponent.h"
#include "QuestDataAsset.h"
#include "QuestObjective.h"

void UActiveQuestObject::Init(UQuestComponent* QuestComponent)
{
	for (TSubclassOf<UQuestObjective> ObjClass : Quest->Objectives)
	{
		if (ObjClass)
		{
			UQuestObjective* Obj = NewObject<UQuestObjective>(QuestComponent, ObjClass);
			Obj->ActivateObjective(QuestComponent->GetOwner());
			Obj->OnCompleted.AddDynamic(this, &UActiveQuestObject::OnObjectiveCompleted);
			Objectives.Add(Obj);
		}
	}
}

void UActiveQuestObject::Deinit()
{
}

void UActiveQuestObject::OnObjectiveCompleted(UQuestObjective* Objective)
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
		OnActiveQuestFinished.Broadcast(this);
	}

}

bool UActiveQuestObject::IsCompleted() const
{
	return bIsCompleted;
}
