// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBlackhole.generated.h"

class USphereComponent;
UCLASS()
class STEALTHGAME_API AFPSBlackhole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSBlackhole();

	UPROPERTY(VisibleAnywhere, Category = "Component")
		UStaticMeshComponent* MeshComp;
	UPROPERTY(VisibleAnywhere, Category = "Component")
		USphereComponent* InnerSphere;
	UPROPERTY(VisibleAnywhere, Category = "Component")
		USphereComponent* OuterSphere;
	UFUNCTION()
		void OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
