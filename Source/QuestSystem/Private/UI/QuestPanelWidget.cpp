// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/QuestPanelWidget.h"

#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "QuestComponent.h"
#include "QuestObjective.h"
#include "QuestWorldSubsystem.h"

void UQuestPanelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC)
	{
		APawn* Pawn = PC->GetPawn();
		if (Pawn)
		{
			QuestComponent = Pawn->FindComponentByClass<UQuestComponent>();
		}
	}

	RefreshQuestList();

	if (UQuestWorldSubsystem* QuestWorldSubsystem = GetWorld()->GetSubsystem<UQuestWorldSubsystem>())
	{
		QuestWorldSubsystem->OnQuestAddedDelegate.AddDynamic(this, &UQuestPanelWidget::OnQuestAdded);
		QuestWorldSubsystem->OnQuestFinishDelegate.AddDynamic(this, &UQuestPanelWidget::OnQuestFinished);
	}
}

void UQuestPanelWidget::RefreshQuestList()
{
	if (!QuestComponent || !QuestListBox) return;

	QuestListBox->ClearChildren();

	const TArray<UQuest*> Quests = QuestComponent->GetActivatedQuests();
	for (UQuest* Quest : Quests)
	{
		if (!Quest->QuestDataAsset) continue;

		if (Quest->bIsCompleted) continue;

		AddQuestToPanel(Quest);
	}
}

void UQuestPanelWidget::OnQuestAdded(class UQuest* NewQuest)
{
	AddQuestToPanel(NewQuest);
}

void UQuestPanelWidget::OnQuestFinished(class UQuest* FinishedQuest)
{
	FinishQuestInPanel(FinishedQuest);
}

void UQuestPanelWidget::AddQuestToPanel(UQuest* NewQuest)
{
	if (QuestEntryWidgetClass)
	{
		UQuestEntry* Entry = CreateWidget<UQuestEntry>(this, QuestEntryWidgetClass);
		if (Entry)
		{
			// TextBlock’ları bulup doldur
			if (UTextBlock* TitleText = Cast<UTextBlock>(Entry->GetWidgetFromName("QuestTitle")))
			{
				TitleText->SetText(FText::FromString(NewQuest->QuestDataAsset->QuestName));
			}

			if (UTextBlock* DescText = Cast<UTextBlock>(Entry->GetWidgetFromName("ObjectiveText")))
			{
				DescText->SetText(NewQuest->Objectives[0]->Description);
			}

			QuestListBox->AddChild(Entry);

			QuestEntryMap.Add({NewQuest,Entry});
		}
	}
}

void UQuestPanelWidget::FinishQuestInPanel(const class UQuest* FinishedQuest)
{
	QuestEntryMap[FinishedQuest]->FinishQuest(this);
}

void UQuestPanelWidget::RemoveFromQuestListBox(UQuestEntry* Entry)
{
	QuestListBox->RemoveChild(Entry);
}
