// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestComponent.h"

#include "QuestDataAsset.h"
#include "QuestObjective.h"
#include "QuestWorldSubsystem.h"
#include "Kismet/GameplayStatics.h"

UQuestComponent::UQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UQuestComponent::OnRegister()
{
	Super::OnRegister();

	QuestWorldSubsystem = GetWorld()->GetSubsystem<UQuestWorldSubsystem>();

	//check (QuestWorldSubsystem)
	
	if (QuestWorldSubsystem)
	{
		QuestWorldSubsystem->RegisterComponent(this);
	}
}

void UQuestComponent::ReadAllQuests(TArray<UQuestDataAsset*> QuestDataList)
{
	for (UQuestDataAsset* QuestData : QuestDataList)
	{
		UQuest* NewActiveQuest = NewObject<UQuest>(this, UQuest::StaticClass());
		NewActiveQuest->QuestDataAsset = QuestData;
		NewActiveQuest->Init(this);
		AllQuestList.Add(NewActiveQuest);
	}
}

void UQuestComponent::ActivateQuest(FString QuestName)
{
	if (UQuest* Quest = GetQuest(QuestName))
	{
		ActivateQuest(Quest);
	}
	// UActiveQuestObject* NewActiveQuest = NewObject<UActiveQuestObject>(this, UActiveQuestObject::StaticClass());
	// NewActiveQuest->Quest = NewQuest;
	// NewActiveQuest->Init(this);
	// 
	//
	// ActivatedQuestList.Add(NewActiveQuest);
	//

}

void UQuestComponent::ActivateQuest(UQuest* Quest)
{
	if (Quest->bIsActivated == true)
	{
		return;
	}
	
	Quest->bIsActivated = true;
	Quest->OnQuestFinished.AddDynamic(this,&UQuestComponent::OnQuestFinished);
	ActivatedQuestList.Add(Quest);
	QuestWorldSubsystem->OnQuestAddedDelegate.Broadcast(Quest);
	OnQuestIsActivated(Quest);
}


void UQuestComponent::OnEventReceived(const FGameplayTag& EventTag)
{
	
	for (UQuest* Quest : AllQuestList)
	{
		Quest->OnEventReceived(EventTag);
		for (UQuestObjective* Objective : Quest->Objectives)
		{
			Objective->OnEventReceived(EventTag);
		}
	}
}

void UQuestComponent::OnQuestFinished(UQuest* Quest)
{
	Quest->OnQuestFinished.RemoveDynamic(this, &UQuestComponent::OnQuestFinished);
	Quest->Deinit();
	QuestWorldSubsystem->OnQuestFinishDelegate.Broadcast(Quest);
	RemoveIconFromMap(Quest);
}

UQuest* UQuestComponent::GetQuest(FString QuestName)
{
	UQuest** Found = Algo::FindByPredicate(AllQuestList, [&](UQuest* Quest)
	{
		return Quest && Quest->GetQuestName() == QuestName;
	});
	return Found ? *Found : nullptr;
}

void UQuestComponent::OnQuestIsActivated(UQuest* Quest)
{
	TArray<AActor*> FoundActors;
	FString TargetAssetTag = Quest->QuestDataAsset->TargetAssetTag;
	UGameplayStatics::GetAllActorsWithTag(this, *TargetAssetTag,FoundActors);

	if (FoundActors.Num() > 0)
		AddIconToMap(Quest, FoundActors[0]);
}

void UQuestComponent::AddIconToMap(UQuest* Quest, AActor* AttachActor)
{
	
}

void UQuestComponent::RemoveIconFromMap(UQuest* Quest)
{
	
}
