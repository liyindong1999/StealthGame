// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StealthGameGameMode.generated.h"

UCLASS(minimalapi)
class AStealthGameGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	//����ͼ�б�¶һ���µ�Class��
	UPROPERTY(EditDefaultsOnly, Category = "Spectaing")
		TSubclassOf<AActor> SpectaingViewPiontClass;
public:
	AStealthGameGameMode();

	void CompleteMission(APawn* InstigatorPawn , bool bMissionSuccess);

	UFUNCTION(BlueprintImplementableEvent,Category = "GameMode")
	void OnMissionCompleted(APawn* InstigatorPawn , bool bMissionSuccess);
};



