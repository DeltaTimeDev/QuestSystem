// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "QuestSystemDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig)
class QUESTSYSTEM_API UQuestSystemDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quests", Config)
	TSoftObjectPtr<class UQuestListDataAsset> QuestDataAsset;
	
};
