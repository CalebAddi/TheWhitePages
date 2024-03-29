#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionBaseComponent.generated.h"

USTRUCT(BlueprintType)
struct FItemInteractValues
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Interaction")
	bool IsButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Interaction")
	bool IsPickup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Interaction")
	bool IsHoldableItem;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Item Interaction")
	bool IsItemPickedUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Interaction")
	bool ShouldDestroyItem;
};


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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hit Interact")
	AActor* PickupActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Interact)
	float InteractHoldTimer = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Interact)
	float CurrentHoldDuration = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Interact)
	float InteractHoldingTime = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Interact)
	float InteractDistance = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Interaction")
	FItemInteractValues ItemValues;


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

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Item Interaction")
	bool IsCurrentlyHoldingItem;


	// Functions
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void ReTriggerDelay();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void DestroyItemOnPickup(const bool& DestroyItem, AActor* ItemToDestroy);

	UFUNCTION(BlueprintCallable, Category = "Helper Function")
	void ResetIsItemPickedUp();
};

#pragma endregion