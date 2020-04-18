// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpPlatform.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AJumpPlatform::AJumpPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverLapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlappingComp"));
	RootComponent = OverLapComp;//设置为根组件
	OverLapComp->SetBoxExtent(FVector(75,75,50));
	OverLapComp->SetHiddenInGame(false);
	//绑定重叠事件函数
	OverLapComp->OnComponentBeginOverlap.AddDynamic(this, &AJumpPlatform::HandleOverlap);

	//创建静态网格组件并将其附属到重叠盒子（OverLapComp）
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(OverLapComp);

	//初始化发射力矩和角度
	LaunchStrenth = 1500;
	LaunchPitchAngle = 35.0f;

}

void AJumpPlatform::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FRotator LaunchDirection = GetActorRotation();//设置发射方向
	LaunchDirection.Pitch += LaunchPitchAngle;//加上初始设置的角度
	FVector LaunchVelocity = LaunchDirection.Vector()*LaunchStrenth;//设置发射速度

	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (OtherCharacter)
	{
		//和Character重叠后发射
		OtherCharacter->LaunchCharacter(LaunchVelocity, true, true);
		//播放粒子效果
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LaunchEffect, GetActorLocation());
	}
	else if(OtherComp && OtherComp->IsSimulatingPhysics())//开启了物理模拟的组件
	{
		//组件重叠后发射
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);
		//播放粒子效果
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LaunchEffect, GetActorLocation());
	}
}




