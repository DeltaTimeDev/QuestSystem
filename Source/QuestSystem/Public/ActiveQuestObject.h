// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ActiveQuestObject.generated.h"

class UActiveQuestObject;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActiveQuestDelegate, UActiveQuestObject*, ActiveQuest);


/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UActiveQuestObject : public UObject
{
	GENERATED_BODY()

public:

	void Init(class UQuestComponent* QuestComponent);
	void Deinit();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UQuestDataAsset* Quest;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class UQuestObjective*> Objectives;

	int32 CurrentObjectiveIndex = 0;

	bool bIsCompleted = false;

	UFUNCTION()
	void OnObjectiveCompleted(UQuestObjective* Objective);
	
	bool IsCompleted() const;

	FActiveQuestDelegate OnActiveQuestFinished;
};
