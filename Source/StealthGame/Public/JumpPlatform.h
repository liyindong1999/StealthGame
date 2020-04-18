// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JumpPlatform.generated.h"
class UBoxComponent;
class UStaticMeshComponent;
class UParticleSystem;
class UArrowComponent;
UCLASS()
class STEALTHGAME_API AJumpPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJumpPlatform();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComp;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent* OverLapComp;
	//处理重叠事件的函数
	UFUNCTION()
		void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//申明发射力矩和发射角度变量
	UPROPERTY(EditInstanceOnly, Category = "JumpPlatform")
		float LaunchStrenth;
	UPROPERTY(EditInstanceOnly, Category = "JumpPlatform")
		float LaunchPitchAngle;
	//创建粒子播放特效
	UPROPERTY(EditDefaultsOnly, Category = "JumpPlatform")
		UParticleSystem* LaunchEffect;
};
