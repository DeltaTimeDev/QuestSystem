// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QuestSystemLibrary.generated.h"

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UQuestSystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "QuestSystem")
	static void BroadcastEvent(UObject* Context, FGameplayTag Event);
	
};
