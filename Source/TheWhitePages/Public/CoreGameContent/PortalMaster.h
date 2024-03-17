// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalMaster.generated.h"

class UBillboardComponent;
class UArrowComponent;
class USceneCaptureComponent2D;
class UBoxComponent;

UCLASS()
class THEWHITEPAGES_API APortalMaster : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	USceneComponent* PortalRootComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* PortalFrame;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* PortalPlane;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	UArrowComponent* ForwardDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	USceneCaptureComponent2D* PortalCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	UBoxComponent* PlayerDetection;

public:	
	APortalMaster();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal Setup", meta=(ExposeOnSpawn=true))
	APortalMaster* LinkedPortal;

private:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Portal Physics", meta=(AllowPrivateAccess = true))
	FVector LastPosition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Portal Physics", meta=(AllowPrivateAccess = true))
	bool LastInFront = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Portal Physics", meta=(AllowPrivateAccess = true))
	float OffsetAmount = -4.f;

};
