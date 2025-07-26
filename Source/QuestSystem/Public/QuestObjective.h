// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "QuestObjective.generated.h"

class UQuestObjective;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FObjectiveDelegate, UQuestObjective*, Objective);

/**
 * 
 */
UCLASS(Blueprintable)
class QUESTSYSTEM_API UQuestObjective : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;

	UPROPERTY(BlueprintReadOnly)
	bool bIsCompleted = false;

	UFUNCTION(BlueprintCallable)
	virtual void ActivateObjective(AActor* Player) {}

	UFUNCTION(BlueprintCallable)
	virtual void CheckObjectiveProgress(AActor* Player) {}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag TriggerEvent;

	UFUNCTION(BlueprintCallable)
	virtual void OnEventReceived(const FGameplayTag& EventTag)
	{
		if (EventTag.MatchesTagExact(TriggerEvent))
		{
			bIsCompleted = true;
			OnCompleted.Broadcast(this);
		}
	}

	FObjectiveDelegate OnCompleted;
	
};
