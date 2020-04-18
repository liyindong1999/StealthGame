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
	RootComponent = OverLapComp;//����Ϊ�����
	OverLapComp->SetBoxExtent(FVector(75,75,50));
	OverLapComp->SetHiddenInGame(false);
	//���ص��¼�����
	OverLapComp->OnComponentBeginOverlap.AddDynamic(this, &AJumpPlatform::HandleOverlap);

	//������̬������������丽�����ص����ӣ�OverLapComp��
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(OverLapComp);

	//��ʼ���������غͽǶ�
	LaunchStrenth = 1500;
	LaunchPitchAngle = 35.0f;

}

void AJumpPlatform::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FRotator LaunchDirection = GetActorRotation();//���÷��䷽��
	LaunchDirection.Pitch += LaunchPitchAngle;//���ϳ�ʼ���õĽǶ�
	FVector LaunchVelocity = LaunchDirection.Vector()*LaunchStrenth;//���÷����ٶ�

	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (OtherCharacter)
	{
		//��Character�ص�����
		OtherCharacter->LaunchCharacter(LaunchVelocity, true, true);
		//��������Ч��
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LaunchEffect, GetActorLocation());
	}
	else if(OtherComp && OtherComp->IsSimulatingPhysics())//����������ģ������
	{
		//����ص�����
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);
		//��������Ч��
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LaunchEffect, GetActorLocation());
	}
}




