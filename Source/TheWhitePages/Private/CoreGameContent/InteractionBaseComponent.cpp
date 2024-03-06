// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGameContent/InteractionBaseComponent.h"

// Sets default values for this component's properties
UInteractionBaseComponent::UInteractionBaseComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

#pragma region "BeginPlay / Tick"

void UInteractionBaseComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UInteractionBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

#pragma endregion

#pragma region "Interaction"

void UInteractionCoreComponent::TraceForInteract(const FVector& Start, const FVector& End)
{
	
}

#pragma endregion

#pragma region "Helper Functions"

void UInteractionBaseComponent::GetCurrentHit(bool& HitIsValid, AActor*& HitActor)
{
	if (IsValid(CurrentHitActor))
	{
		HitIsValid = true;
		HitActor = CurrentHitActor;
	}
	else
	{
		HitIsValid = false;
		HitActor = nullptr;
	}
}

void UInteractionBaseComponent::GetPreviousHit(bool& HitIsValid, AActor*& HitActor)
{
	if (IsValid(PrevHitActor))
	{
		HitIsValid = true;
		HitActor = PrevHitActor;
	}
	else
	{
		HitIsValid = false;
		HitActor = nullptr;
	}
}

void UInteractionBaseComponent::EnableHitRecheck()
{
	RecheckHit = true;
}

void UInteractionBaseComponent::DisableHitRecheck()
{
	RecheckHit = false;
}

void UInteractionBaseComponent::GetRecheckHit(bool& ReturnValue)
{
	if (RecheckHit)
		ReturnValue = true;

	else
		ReturnValue = false;
}

void UInteractionBaseComponent::UpdateInteractState(bool HitResult)
{
	// Purpose of this function is to be overriden
}

void UInteractionCoreComponent::ReTriggerDelay()
{
	if (IsTriggerDelay)
		IsTriggerDelay = false;

	else
	{
		IsTriggerDelay = true;

		FTimerDelegate TimerDel;
		TimerDel.BindUFunction(this, FName("ReTriggerDelay"));
		const float Delay = 0.0001f;
		FTimerHandle TimeDelayHandle;

		GetWorld()->GetTimerManager().SetTimer(TimeDelayHandle, TimerDel, Delay, false);
	}
}

#pragma endregion