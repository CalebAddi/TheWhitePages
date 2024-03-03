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
void UPlayerAbilitiesComponent::StartSprint()
{
	MovementComponentRef->MaxWalkSpeed = SprintSpeed;
	IsSprinting = true;
}

void UPlayerAbilitiesComponent::StopSprint()
{
	MovementComponentRef->MaxWalkSpeed = WalkingSpeed;
	IsSprinting = false;
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
