#include "CoreGameContent/AI/BTTasks/BTTask_FocusToTarget.h"
#include "CoreGameContent/AI/EnemyMasterController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

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
                FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
                return EBTNodeResult::Succeeded;
            }
            else
            {
                FVector Location = BlackboardComp->GetValueAsVector(FocusTargetKey.SelectedKeyName);
                FNavLocation ProjectedLocation;

                if (auto* const NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(Controller->GetWorld()))
                {
                    if (NavSys->ProjectPointToNavigation(Location, ProjectedLocation))
                    {
                        Controller->SetFocalPoint(ProjectedLocation.Location);
                        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
                        return EBTNodeResult::Succeeded;
                    }
                }
            }
        }
    }
    return EBTNodeResult::Failed;
}