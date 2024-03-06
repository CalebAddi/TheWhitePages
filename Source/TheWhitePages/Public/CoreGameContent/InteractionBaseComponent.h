// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionBaseComponent.generated.h"


#pragma region "Base Component Class"

UCLASS( Blueprintable, meta=(BlueprintSpawnableComponent) )
class THEWHITEPAGES_API UInteractionBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractionBaseComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hit Interact")
	AActor* CurrentHitActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hit Interact")
	AActor* PrevHitActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Interact)
	float InteractHoldTimer = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Interact)
	float CurrentHoldDuration = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Interact)
	float InteractHoldingTime = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Interact)
	float InteractDistance = 0.f;


	// Functions
	UFUNCTION(BlueprintPure, Category = "Hit Interact")
	void GetCurrentHit(bool& HitIsValid, AActor*& HitActor);

	UFUNCTION(BlueprintPure, Category = "Hit Interact")
	void GetPreviousHit(bool& HitIsValid, AActor*& HitActor);

	UFUNCTION(BlueprintPure, Category = "Hit Interact")
	void GetRecheckHit(bool& ReturnValue);

	UFUNCTION(BlueprintCallable, Category = "Hit Interact")
	void EnableHitRecheck();

	UFUNCTION(BlueprintCallable, Category = "Hit Interact")
	void DisableHitRecheck();

	// UFUNCTION(BlueprintCallable, Category = "Override Function")
	// void UpdateInteractState(bool HitResult); // not using the & gives it a checkbox input

private:	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = true), Category = "Hit Interact")
	bool RecheckHit;

};

#pragma endregion

#pragma region "Core Component Class"

UCLASS(Blueprintable)
class THEWHITEPAGES_API UInteractionCoreComponent : public UInteractionBaseComponent
{
	GENERATED_BODY()

public:


protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Interact Ticks")
	bool CanSetPrevious;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interact Ticks")
	bool IsUpdateOnTick;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Interact Ticks")
	bool IsTriggerDelay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interact Ticks")
	float UpdateFrequency;


	// Functions
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void TraceForInteract(const FVector& Start, const FVector& End);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void ReTriggerDelay();
};

#pragma endregion