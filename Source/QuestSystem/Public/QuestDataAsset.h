// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "QuestDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UQuestDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString QuestDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag ActivateQuestEvent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ActivateQuestNameAfterFinish;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ActivationDelay = 2;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<class UQuestObjective>> Objectives;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsRepeatable = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString TargetAssetTag = "None";
	
};

UCLASS()
class QUESTSYSTEM_API UQuestListDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UQuestDataAsset*> QuestList;
};
