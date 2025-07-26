// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* QuestListBox;

	/** Her görev için kullanılacak alt widget (BP'den atanır) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> QuestEntryWidgetClass;

	/** Görev component'i */
	UPROPERTY()
	class UQuestComponent* QuestComponent;

	UFUNCTION()
	void OnQuestAdded(bool bNewValue);

	UFUNCTION()
	void OnQuestFinished(bool bNewValue);
};
