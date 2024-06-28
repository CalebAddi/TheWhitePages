#include "DevelopmentContent/PlayerAbilitiesComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UPlayerAbilitiesComponent::UPlayerAbilitiesComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	CharacterOwner = Cast<ACharacter>(GetOwner());
}

#pragma region "BeginPlay / Event Tick"

// Called when the game starts
void UPlayerAbilitiesComponent::BeginPlay()
{
	Super::BeginPlay();
	MovementComponentRef = CharacterOwner ? CharacterOwner->GetCharacterMovement() : nullptr;
}


// Called every frame
void UPlayerAbilitiesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

#pragma endregion

#pragma region "Stamina"

void UPlayerAbilitiesComponent::DrainStamina()
{
	StaminaRegenValues.IsRegenStamina = false;

	float StaminaClampCalc = StaminaValue.CurrStamina - StaminaDrainValues.StaminaDrainAmount * StaminaDrainValues.StaminaDrainAdjustCalc;
	StaminaValue.CurrStamina = FMath::Clamp(StaminaClampCalc, 0.f, StaminaValue.MaxStamina);

	if (StaminaValue.CurrStamina == 0.f)
	{
		StopSprint();
		StaminaDrainValues.IsDrainingStamina = false;
	}

	else if (MovementValue.IsSprinting && MovementValue.IsMoving && !StaminaRegenValues.IsRegenStamina)
	{
		float SprintDelay = 0.05f;
		GetWorld()->GetTimerManager().SetTimer(StaminaTimeHandle, this, &UPlayerAbilitiesComponent::StaminaLoopDrain, SprintDelay, false);
	}

	else
	{
		StaminaDrainValues.IsDrainingStamina = false;
	}
}

void UPlayerAbilitiesComponent::RegenStamina()
{
	float StaminaClampCalc = StaminaValue.CurrStamina + StaminaRegenValues.StaminaRegenAmount * StaminaRegenValues.StaminaRegenAdjustCalc;
	StaminaValue.CurrStamina = FMath::Clamp(StaminaClampCalc, 0.f, StaminaValue.MaxStamina);

	if (StaminaValue.CurrStamina != 0 && !MovementValue.IsSprinting && !StaminaDrainValues.IsDrainingStamina)
	{
		float SprintDelay = 0.55f;
		GetWorld()->GetTimerManager().SetTimer(StaminaTimeHandle, this, &UPlayerAbilitiesComponent::StaminaLoopRegain, SprintDelay, false);
	}
}

void UPlayerAbilitiesComponent::StartSprint()
{
	if (MovementComponentRef)
	{
		MovementComponentRef->MaxWalkSpeed = MovementValue.SprintSpeed;
		MovementValue.IsSprinting = true;
		DrainStamina();
	}
}

void UPlayerAbilitiesComponent::StopSprint()
{
	if (MovementComponentRef)
	{
		MovementComponentRef->MaxWalkSpeed = MovementValue.WalkSpeed;
		MovementValue.IsSprinting = false;
		float RegenDelayAmount = 1.f;
		GetWorld()->GetTimerManager().SetTimer(StaminaTimeHandle, this, &UPlayerAbilitiesComponent::RegenDelay, RegenDelayAmount, false);
	}
}

#pragma endregion

#pragma region "Dashing"

void UPlayerAbilitiesComponent::StartDash()
{
	if (!DashValue.CanDash || DashValue.IsDashing || StaminaValue.CurrStamina <= 15.f || !CharacterOwner)
		return;

	FVector DashDir;
	if (CharacterOwner)
	{
		if (!MovementValue.IsMoving)
		{
			DashDir = CharacterOwner->GetActorForwardVector();
		}
		else 
		{
			DashDir = CharacterOwner->GetLastMovementInputVector();
		}

		MovementComponentRef->BrakingFrictionFactor = 0.f;
		DashDir.Normalize();
		CharacterOwner->LaunchCharacter(DashDir * DashValue.DashSpeed, true, true);
	}

	DashValue.IsDashing = true;
	DashValue.CanDash = false;

	GetWorld()->GetTimerManager().SetTimer(DashTimeHandle, this, &UPlayerAbilitiesComponent::StopDash, DashValue.DashDuration, false);
	GetWorld()->GetTimerManager().SetTimer(DashCooldownHandle, this, &UPlayerAbilitiesComponent::ResetDashCooldown, DashValue.DashCoolDown, false);
}

void UPlayerAbilitiesComponent::StopDash()
{
	DashValue.IsDashing = false;
	MovementComponentRef->StopMovementImmediately();
	MovementComponentRef->BrakingFrictionFactor = 2.f;
}

void UPlayerAbilitiesComponent::ResetDashCooldown()
{
	DashValue.CanDash = true;
}

#pragma endregion

#pragma region "Helper Functions"

void UPlayerAbilitiesComponent::StaminaLoopDrain()
{
	StaminaDrainValues.IsDrainingStamina = true;
	DrainStamina();
}

void UPlayerAbilitiesComponent::StaminaLoopRegain()
{
	StaminaRegenValues.IsRegenStamina = true;

	if (StaminaValue.CurrStamina == StaminaValue.MaxStamina)
	{
		StaminaRegenValues.IsRegenStamina = false;
	}
	else
	{
		RegenStamina();
	}
}

void UPlayerAbilitiesComponent::RegenDelay()
{
	RegenStamina();
}

void UPlayerAbilitiesComponent::KillPlayer(const bool& IsPlayerDead)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (CharacterOwner && PlayerController && IsPlayerDead)
	{
		CharacterOwner->DisableInput(PlayerController);
		CharacterOwner->K2_DestroyActor();
	}
}

#pragma endregion
