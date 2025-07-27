// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestEntry.generated.h"

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UQuestEntry : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget),BlueprintReadOnly)
	class UQuestTick* QuestTick;

	UFUNCTION(BlueprintCallable)
	void FinishQuest(class UQuestPanelWidget* PanelWidget);

public:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayFinishAnimation();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FinishAnimDelay = 2;
};
