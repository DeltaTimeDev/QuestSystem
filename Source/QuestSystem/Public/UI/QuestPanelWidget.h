// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestEntry.h"
#include "Blueprint/UserWidget.h"
#include "QuestPanelWidget.generated.h"

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UQuestPanelWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	/** Görevleri gösterir */
	UFUNCTION(BlueprintCallable)
	void RefreshQuestList();

protected:
	/** Scroll alanı: her görevin ekleneceği yer */
	UPROPERTY(meta = (BindWidget),BlueprintReadOnly)
	class UVerticalBox* QuestListBox;

	/** Her görev için kullanılacak alt widget (BP'den atanır) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> QuestEntryWidgetClass;

	UPROPERTY()
	TMap<class UQuest*, UQuestEntry*> QuestEntryMap;
	/** Görev component'i */
	UPROPERTY()
	class UQuestComponent* QuestComponent;

	UFUNCTION()
	void OnQuestAdded(class UQuest* NewQuest);

	UFUNCTION()
	void OnQuestFinished(class UQuest* NewQuest);


	UFUNCTION()
	void AddQuestToPanel(class UQuest* NewQuest);

	UFUNCTION()
	void FinishQuestInPanel(const class UQuest* FinishedQuest);

public:
	UFUNCTION()
	void RemoveFromQuestListBox(UQuestEntry* Entry);
};
