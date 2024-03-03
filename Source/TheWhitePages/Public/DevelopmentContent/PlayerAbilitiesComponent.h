#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerAbilitiesComponent.generated.h"

class UCharacterMovementComponent;

UCLASS( Blueprintable, meta=(BlueprintSpawnableComponent) )
class THEWHITEPAGES_API UPlayerAbilitiesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerAbilitiesComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected: // Variables 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	UCharacterMovementComponent* MovementComponentRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	bool IsMoving;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stamina)
	float CurrStamina = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stamina)
	float MaxStamina = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sprint)
	float SprintSpeed = 650.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sprint)
	float WalkingSpeed = 400.f;

protected: // Functions

	virtual void BeginPlay() override;

private: // Variables
	UPROPERTY()
	FTimerHandle DashTimeHandle;

	UPROPERTY()
	FTimerHandle DashCooldownHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = true), Category=Sprint)
	bool IsSprinting;

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

	ACharacter* CharacterOwner;

private: // Functions

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

};
