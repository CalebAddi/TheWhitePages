#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetPassiveState.generated.h"

/**
 * 
 */
UCLASS()
class THEWHITEPAGES_API UBTTask_SetPassiveState : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_SetPassiveState(const FObjectInitializer& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:


private:


};
