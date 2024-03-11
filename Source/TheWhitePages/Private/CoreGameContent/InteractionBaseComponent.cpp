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
	// Currently not finished
	// FHitResult HitResult;
    // FCollisionQueryParams QueryParams;
    // QueryParams.AddIgnoredActor(GetOwner());
    // QueryParams.bTraceComplex = false;

	// bool HitCollide = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams);

	// if (HitCollide)
	// {
	// 	AActor* HitActor = HitResult.GetActor();
	// 	if (HitActor != CurrentHitActor)
	// 	{
	// 		PrevHitActor = CurrentHitActor;
    //         CurrentHitActor = HitActor; 
    //         CanSetPrevious = true;
    //         CurrentHoldDuration = 0.f;
    //         // UpdateInteractState(true);
	// 	}
	// 	else
	// 	{
	// 		bool LocRecheckHit;
	// 		GetRecheckHit(LocRecheckHit);

	// 		if (LocRecheckHit)
	// 		{
	// 			DisableHitRecheck();
	// 			// UpdateInteracState(true);
	// 		}
	// 	}
	// }
	// else
	// {
	// 	// Placeholder
	// }
}

void UInteractionCoreComponent::DestroyItemOnPickup(const bool& DestroyItem, AActor* ItemToDestroy)
{
	if (DestroyItem)
	{
		if (ItemToDestroy)
		{
			ItemToDestroy->Destroy();
			IsItemPickedUp = true;

			FTimerHandle TimerHandle;
			float DelayTime = 0.5;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UInteractionCoreComponent::ResetIsItemPickedUp, DelayTime, false);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Item cast failed, or GetOwner() returned nullptr."));
		}
	}
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
	ReturnValue = RecheckHit;
}

// void UInteractionBaseComponent::UpdateInteractState(bool HitResult)
// {
// 	// Purpose of this function is to be overriden
// }

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

void UInteractionCoreComponent::ResetIsItemPickedUp()
{
	IsItemPickedUp = false;
}

#pragma endregion
