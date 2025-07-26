// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/WorldSubsystem.h"
#include "QuestWorldSubsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQuestEventDelegate, bool, NewValue);

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UQuestWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	class UQuestListDataAsset* QuestDataAsset;

	UPROPERTY()
	class UQuestComponent* QuestComponent;

public:
	void RegisterComponent(UQuestComponent* InQuestComponent);

	void BroadcastEvent(const FGameplayTag& EventTag);

	UPROPERTY(BlueprintAssignable)
	FQuestEventDelegate OnQuestAddedDelegate;

	UPROPERTY(BlueprintAssignable)
	FQuestEventDelegate OnQuestFinishDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FQuestEventDelegate OnFirstStepFieldDelegate;


	UFUNCTION(BlueprintCallable)
	void FirstStepFieldBroadcast(bool Value);
	
private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION()
	void OnFirstStepField(bool bArg);
};
