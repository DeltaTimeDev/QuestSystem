// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/WorldSubsystem.h"
#include "QuestWorldSubsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQuestEventDelegate, class UQuest*, Quest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventDelegate, bool, NewValue);

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UQuestWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()


private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	UFUNCTION(BlueprintCallable)
	void Init();
	
	UPROPERTY()
	class UQuestComponent* QuestComponent;
	
	UPROPERTY()
    class UQuestListDataAsset* QuestDataAsset;

public:

	void GetQuestDataList(TArray<class UQuestDataAsset*>& DataList);

	
	void RegisterComponent(UQuestComponent* InQuestComponent);

	void BroadcastEvent(const FGameplayTag& EventTag);

	UPROPERTY(BlueprintAssignable)
	FQuestEventDelegate OnQuestAddedDelegate;

	UPROPERTY(BlueprintAssignable)
	FQuestEventDelegate OnQuestFinishDelegate;
	
};
