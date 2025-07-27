// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "Quest.generated.h"


class UQuest;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQuestDelegate, UQuest*, ActiveQuest);

UCLASS()
class QUESTSYSTEM_API UQuest : public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UQuestDataAsset* QuestDataAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class UQuestObjective*> Objectives;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UQuestComponent* QuestComponent;

	bool bIsActivated = false;
	bool bIsCompleted = false;

	FQuestDelegate OnQuestFinished;


	
	void Init(class UQuestComponent* InQuestComponent);
	
	void Deinit();

	UFUNCTION()
	void OnObjectiveCompleted(UQuestObjective* Objective);

	UFUNCTION()
	void OnQuestCompleted();

	bool IsActivated() const { return bIsActivated; }
	bool IsCompleted() const { return bIsCompleted; }
	FString GetQuestName();


	UFUNCTION(BlueprintCallable)
	virtual void OnEventReceived(const FGameplayTag& EventTag);
};
