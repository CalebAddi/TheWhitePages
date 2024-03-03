#include "DevelopmentContent/PlayerAbilitiesComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UPlayerAbilitiesComponent::UPlayerAbilitiesComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	CharacterOwner = Cast<ACharacter>(GetOwner());
	IsMoving = false;
}

#pragma region "BeginPlay / Event Tick"

// Called when the game starts
void UPlayerAbilitiesComponent::BeginPlay()
{
	Super::BeginPlay();
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

	float StaminaClampCalc = CurrStamina - StaminaDrainValues.StaminaDrainAmount * StaminaDrainValues.StaminaDrainAdjustCalc;
	CurrStamina = FMath::Clamp(StaminaClampCalc, 0.f, MaxStamina);

	if (CurrStamina == 0.f)
	{
		StopSprint();
		StaminaDrainValues.IsDrainingStamina = false;
	}

	else if (IsSprinting && IsMoving && !StaminaRegenValues.IsRegenStamina)
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
	float StaminaClampCalc = CurrStamina + StaminaRegenValues.StaminaRegenAmount * StaminaRegenValues.StaminaRegenAdjustCalc;
	CurrStamina = FMath::Clamp(StaminaClampCalc, 0.f, MaxStamina);

	if (CurrStamina != 0 && !IsSprinting && !StaminaDrainValues.IsDrainingStamina)
	{
		float SprintDelay = 0.55f;
		GetWorld()->GetTimerManager().SetTimer(StaminaTimeHandle, this, &UPlayerAbilitiesComponent::StaminaLoopRegain, SprintDelay, false);
	}
}

void UPlayerAbilitiesComponent::StartSprint()
{
	MovementComponentRef->MaxWalkSpeed = SprintSpeed;
	IsSprinting = true;
	DrainStamina();
}

void UPlayerAbilitiesComponent::StopSprint()
{
	MovementComponentRef->MaxWalkSpeed = WalkingSpeed;
	IsSprinting = false;
	float RegenDelayAmount = 1.f;
	GetWorld()->GetTimerManager().SetTimer(StaminaTimeHandle, this, &UPlayerAbilitiesComponent::RegenDelay, RegenDelayAmount, false);
}

#pragma endregion

#pragma region "Dashing"

void UPlayerAbilitiesComponent::StartDash()
{
	if (!CanDash || IsDashing || CurrStamina <= 25.f)
		return;

	FVector DashDir;
	if (CharacterOwner)
	{
		if (!IsMoving)
		{
			DashDir = CharacterOwner->GetActorForwardVector();
		}
		else 
		{
			DashDir = CharacterOwner->GetLastMovementInputVector();
		}

		MovementComponentRef->BrakingFrictionFactor = 0.f;
		DashDir.Normalize();
		CharacterOwner->LaunchCharacter(DashDir * DashSpeed, true, true);
	}

	IsDashing = true;
	CanDash = false;

	GetWorld()->GetTimerManager().SetTimer(DashTimeHandle, this, &UPlayerAbilitiesComponent::StopDash, DashDuration, false);
	GetWorld()->GetTimerManager().SetTimer(DashCooldownHandle, this, &UPlayerAbilitiesComponent::ResetDashCooldown, DashCoolDown, false);
}

void UPlayerAbilitiesComponent::StopDash()
{
	IsDashing = false;
	MovementComponentRef->StopMovementImmediately();
	MovementComponentRef->BrakingFrictionFactor = 2.f;
}

void UPlayerAbilitiesComponent::ResetDashCooldown()
{
	CanDash = true;
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

	if (CurrStamina == MaxStamina)
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

#pragma endregion