#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerAbilitiesComponent.generated.h"

class UCharacterMovementComponent;

#pragma region "Structs"

USTRUCT(BlueprintType)
struct FMovementValues
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
	bool IsMoving;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = true), Category=Movement)
	bool IsSprinting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float SprintSpeed = 650.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float WalkSpeed = 400.f;
};

USTRUCT(BlueprintType)
struct FStaminaValues
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stamina)
	float CurrStamina = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stamina)
	float MaxStamina = 100.f;
};

USTRUCT(BlueprintType)
struct FStaminaDrain
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stamina)
	float StaminaDrainAmount = 2.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stamina)
	float StaminaDrainAdjustCalc = 0.07f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stamina)
	bool IsDrainingStamina = false;
};

USTRUCT(BlueprintType)
struct FStaminaRegain
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stamina)
	float StaminaRegenAmount = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stamina)
	float StaminaRegenAdjustCalc = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stamina)
	bool IsRegenStamina = false;
};

USTRUCT(BlueprintType)
struct FDashValues
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = true), Category=Dashing)
	bool CanDash = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = true), Category=Dashing)
	bool IsDashing;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = true), Category=Dashing)
	float DashSpeed = 1500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = true), Category=Dashing)
	float DashDuration = 0.2f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = true), Category=Dashing)
	float DashCoolDown = 2.f;
};

#pragma endregion

UCLASS( Blueprintable, meta=(BlueprintSpawnableComponent) )
class THEWHITEPAGES_API UPlayerAbilitiesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerAbilitiesComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
virtual void BeginPlay() override;

	// Variables
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
	UCharacterMovementComponent* MovementComponentRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
	FMovementValues MovementValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stamina)
	FStaminaValues StaminaValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stamina)
	FStaminaDrain StaminaDrainValues;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stamina)
	FStaminaRegain StaminaRegenValues;

	//Functions
	UFUNCTION(BlueprintCallable, Category = Stamina)
	void DrainStamina();

	UFUNCTION(BlueprintCallable, Category = Stamina)
	void RegenStamina();

	UFUNCTION(BlueprintCallable, Category = Health)
	void KillPlayer(const bool& IsPlayerDead);

private:
	//Variables
	ACharacter* CharacterOwner;

	UPROPERTY()
	FTimerHandle DashTimeHandle;

	UPROPERTY()
	FTimerHandle DashCooldownHandle;

	UPROPERTY()
	FTimerHandle StaminaTimeHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = true), Category=Dashing)
	FDashValues DashValue;

	//Functions
	UFUNCTION(BlueprintCallable, meta=(AllowPrivateAccess = true), Category = Sprint)
	void StartSprint();

	UFUNCTION(BlueprintCallable, meta=(AllowPrivateAccess = true), Category = Sprint)
	void StopSprint();

	UFUNCTION(BlueprintCallable, meta=(AllowPrivateAccess = true), Category = Dashing)
	void StartDash();

	UFUNCTION()
	void StopDash();

	UFUNCTION()
	void ResetDashCooldown();

	UFUNCTION()
	void StaminaLoopDrain();

	UFUNCTION()
	void StaminaLoopRegain();

	UFUNCTION()
	void RegenDelay();

};
