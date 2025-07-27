// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/QuestEntry.h"

#include "UI/QuestPanelWidget.h"
#include "UI/QuestTick.h"

void UQuestEntry::FinishQuest(UQuestPanelWidget* PanelWidget)
{
	QuestTick->Ticking();


	FTimerHandle AnimTimerHandle;

	GetWorld()->GetTimerManager().SetTimer(
		AnimTimerHandle,
		[this]()
		{
			PlayFinishAnimation();
		},
		FinishAnimDelay,
		false
	);

	FTimerHandle RemoveTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		RemoveTimerHandle,
		[this, PanelWidget]()
		{
			PanelWidget->RemoveFromQuestListBox(this);
		},
		FinishAnimDelay + 0.75f,
		false
	);
}
