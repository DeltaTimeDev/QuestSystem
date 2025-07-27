// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestTick.generated.h"

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UQuestTick : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void Ticking();
};
