#include "CoreGameContent/AI/BTTasks/BTTask_SetPassiveState.h"
#include "CoreGameContent/AI/EnemyMasterController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_SetPassiveState::UBTTask_SetPassiveState(const FObjectInitializer& ObjectInitializer)
{
    NodeName = "Set Passive State";
}

EBTNodeResult::Type UBTTask_SetPassiveState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (auto* const EnemyController = Cast<AEnemyMasterController>(OwnerComp.GetAIOwner()))
    {
        EnemyController->SetStateAsPassive();

        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}