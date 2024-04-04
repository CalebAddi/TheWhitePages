#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyMasterController.generated.h"

USTRUCT(BlueprintType)
struct FKeyNameVariables
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Keys)
	FName TargetKeyName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Keys)
	FName StateKeyName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Keys)
	FName POIKeyName;
};

UENUM(BlueprintType)
enum class EAIEnemyState : uint8
{
	Passive UMETA(DisplayName="Passive"),
	Aggro UMETA(DisplayName="Aggro"),
	Frozen UMETA(DisplayName="Frozen"),
	Searching UMETA(DisplayName="Searching")
};

UENUM(BlueprintType)
enum class EAIDetectionState : uint8
{
	None UMETA(DisplayName="None"),
	Sight UMETA(DisplayName="Sight"),
	Hearing UMETA(DisplayName="Hearing")
};

UCLASS()
class THEWHITEPAGES_API AEnemyMasterController : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI State")
	EAIEnemyState EnemyState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI State")
	EAIDetectionState DetectState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Tree)
	UBehaviorTree* BehaviorTreeAsset;

	UFUNCTION(BlueprintCallable, Category = "AI State")
	void SetStateAsPassive();

	UFUNCTION(BlueprintCallable, Category = "AI State")
	void SetStateAsSearching(const FVector& Location);

	UFUNCTION(BlueprintCallable, Category = "AI State")
	void SetStateAsAttacking(AActor* AttackTarget);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Keys)
	FKeyNameVariables KeyNames;

	UFUNCTION(BlueprintCallable, Category = Tree)
	void InstantiateBehaviorTree();

	UFUNCTION(BlueprintCallable, Category = "AI State")
	void GetCurrentState(EAIEnemyState& State) const;

	UFUNCTION(BlueprintCallable, Category = "AI Detection")
	void HandleSensedSight(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "AI Detection")
	void HandleSensedSound(const FVector& SoundLocation);


private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Blackboard, meta=(AllowPrivateAccess="true"))
	UBlackboardComponent* BlackboardComp;

};
