// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveQuestObject.h"
#include "GameplayTagContainer.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UActiveQuestObject*> PassiveQuestList;

    /** Aktif görev listesi */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TArray<UActiveQuestObject*> ActivatedQuestList;

	 
    /** Görev başlatır */
    UFUNCTION(BlueprintCallable)
    void StartQuest(class UQuestDataAsset* NewQuest);
	
    /** UI için basit getter */
    UFUNCTION(BlueprintPure)
    const TArray<class UActiveQuestObject*> GetActivatedQuests() const { return ActivatedQuestList; }

	
	void OnEventReceived(const FGameplayTag& EventTag);

	UFUNCTION()
	void OnActiveQuestFinished(UActiveQuestObject* ActiveQuest);
};
