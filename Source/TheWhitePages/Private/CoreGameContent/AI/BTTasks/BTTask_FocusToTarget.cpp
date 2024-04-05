#include "CoreGameContent/AI/BTTasks/BTTask_FocusToTarget.h"
#include "CoreGameContent/AI/EnemyMasterController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FocusToTarget::UBTTask_FocusToTarget(const FObjectInitializer& ObjectInitializer)
{
    NodeName = "Focus On Target";
}

EBTNodeResult::Type UBTTask_FocusToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (auto* const BlackboardComp = OwnerComp.GetBlackboardComponent())
    {
        if (auto* const Controller = Cast<AEnemyMasterController>(OwnerComp.GetAIOwner()))
        {
            if (AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(FocusTargetKey.SelectedKeyName)))
            {
                Controller->SetFocus(TargetActor);
            }

            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
            return EBTNodeResult::Succeeded;
        }
    }
    return EBTNodeResult::Failed;
}