#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyMasterController.generated.h"


UENUM(BlueprintType)
enum class EAIEnemyState : uint8
{
	Passive UMETA(DisplayName="Passive"),
	Aggro UMETA(DisplayName="Aggro"),
	Frozen UMETA(DisplayName="Frozen"),
	Searching UMETA(DisplayName="Searching")
};

UCLASS()
class THEWHITEPAGES_API AEnemyMasterController : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI State")
	EAIEnemyState EnemyState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Tree)
	UBehaviorTree* BehaviorTreeAsset;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Keys)
	FName TargetKeyName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Keys)
	FName StateKeyName;

	UFUNCTION(BlueprintCallable, Category = Tree)
	void InstantiateBehaviorTree();

	UFUNCTION(BlueprintCallable, Category = "AI State")
	void SetStateAsPassive();

	UFUNCTION(BlueprintCallable, Category = "AI State")
	void SetStateAsAttacking(AActor* AttackTarget);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Blackboard, meta=(AllowPrivateAccess="true"))
	UBlackboardComponent* BlackboardComp;

};
