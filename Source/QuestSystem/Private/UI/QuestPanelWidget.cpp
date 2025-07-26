// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/QuestPanelWidget.h"

#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "ActiveQuestObject.h"
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

	const TArray<UActiveQuestObject*> Quests = QuestComponent->GetActivatedQuests();
	for (const UActiveQuestObject* Quest : Quests)
	{
		if (!Quest->Quest) continue;

		if (Quest->bIsCompleted) continue;

		// Alt widget oluştur
		if (QuestEntryWidgetClass)
		{
			UUserWidget* Entry = CreateWidget<UUserWidget>(this, QuestEntryWidgetClass);
			if (Entry)
			{
				// TextBlock’ları bulup doldur
				if (UTextBlock* TitleText = Cast<UTextBlock>(Entry->GetWidgetFromName("QuestTitle")))
				{
					TitleText->SetText(Quest->Quest->QuestName);
				}

				if (UTextBlock* DescText = Cast<UTextBlock>(Entry->GetWidgetFromName("ObjectiveText")))
				{
					if (Quest->Objectives.IsValidIndex(Quest->CurrentObjectiveIndex))
					{
						DescText->SetText(Quest->Objectives[Quest->CurrentObjectiveIndex]->Description);
					}
				}

				QuestListBox->AddChild(Entry);
			}
		}
	}
}

void UQuestPanelWidget::OnQuestAdded(bool bNewValue)
{
	RefreshQuestList();
}

void UQuestPanelWidget::OnQuestFinished(bool bNewValue)
{
	RefreshQuestList();
}
