// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Quest.h"
#include "QuestDataAsset.h"
#include "Components/ActorComponent.h"
#include "QuestComponent.generated.h"

class UQuestComponent;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUESTSYSTEM_API UQuestComponent : public UActorComponent
{
	    GENERATED_BODY()

public:	
    UQuestComponent();

	virtual void OnRegister() override;

	void ReadAllQuests(TArray<UQuestDataAsset*> QuestDataList);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UQuest*> AllQuestList;

    /** Aktif görev listesi */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TArray<UQuest*> ActivatedQuestList;

	 
    /** Görev başlatır */
    UFUNCTION(BlueprintCallable)
    void ActivateQuest(FString QuestName);
	
	void ActivateQuest(UQuest* Quest);
	
    /** UI için basit getter */
    UFUNCTION(BlueprintPure)
    const TArray<UQuest*> GetActivatedQuests() const { return ActivatedQuestList; }

	
	void OnEventReceived(const FGameplayTag& EventTag);

	UFUNCTION()
	void OnQuestFinished(UQuest* Quest);

	UQuest* GetQuest(FString QuestName);


	// Catche data
	UPROPERTY()
	class UQuestWorldSubsystem* QuestWorldSubsystem;

	virtual void OnQuestIsActivated(UQuest* Quest);
	virtual void AddIconToMap(AActor* AttachActor);
	
};
