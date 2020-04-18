// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "StealthGameGameMode.h"
#include "StealthGameHUD.h"
#include "StealthGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet//GameplayStatics.h"
#include "FPSGameState.h"
#include "Engine/World.h"

AStealthGameGameMode::AStealthGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AStealthGameHUD::StaticClass();

	GameStateClass = AFPSGameState::StaticClass();
}

void AStealthGameGameMode::CompleteMission(APawn* InstigatorPawn ,bool bMissionSuccess)
{
	if (InstigatorPawn)
	{
		//������ҿ������Ŀ���
		InstigatorPawn->DisableInput(nullptr);
		if (SpectaingViewPiontClass)
		{
			TArray<AActor*> ReturnedActors;
			//��ȡͬһ��Class������Actor���󣬽��䴢����������
			UGameplayStatics::GetAllActorsOfClass(this,SpectaingViewPiontClass,ReturnedActors);

			if (ReturnedActors.Num() > 0)
			{

				AActor* NewViewTarget = ReturnedActors[0];
				for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
				{
					APlayerController* PC = It->Get();
					if (PC) 
					{
						//��NewViewTarget���ӽ�����Ϊ��ҿ��������ӽ�
						PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
					}
				}
				
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SpectaingViewPiontClass is nullptr"));
		}
	}
	AFPSGameState* GS = GetGameState<AFPSGameState>();
	if (GS)
	{
		GS->MulticastOnMissionComplete(InstigatorPawn, bMissionSuccess);
	}
	OnMissionCompleted(InstigatorPawn,bMissionSuccess);

	
}
