// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSystemLibrary.h"

#include "QuestWorldSubsystem.h"

void UQuestSystemLibrary::BroadcastEvent(UObject* Context, FGameplayTag Event)
{
	if (UQuestWorldSubsystem* QuestWorldSubsystem = Context->GetWorld()->GetSubsystem<UQuestWorldSubsystem>())
	{
		QuestWorldSubsystem->BroadcastEvent(Event);
	}
}
