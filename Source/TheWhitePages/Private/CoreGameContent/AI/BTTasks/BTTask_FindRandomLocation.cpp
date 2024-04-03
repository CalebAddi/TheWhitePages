#include "CoreGameContent/AI/BTTasks/BTTask_FindRandomLocation.h"
#include "NavigationSystem.h"
#include "CoreGameContent/AI/EnemyMasterController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(const FObjectInitializer& ObjectInitializer)
{
    NodeName = "Move To Random Location";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (auto* const EnemyController = Cast<AEnemyMasterController>(OwnerComp.GetAIOwner()))
    {
        if (auto* const Enemy = EnemyController->GetPawn())
        {
            auto const OriginVect = Enemy->GetActorLocation(); // get enemy loc to use as an origin

            if (auto* const NavSys = UNavigationSystemV1::GetCurrent(Enemy->GetWorld())) // get nav sys and generate a random loc
            {
                FNavLocation Loc;
                if (NavSys->GetRandomPointInNavigableRadius(OriginVect, SearchRadius, Loc))
                {
                    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
                }

                FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
                return EBTNodeResult::Succeeded;
            }
        }
    }

    return EBTNodeResult::Failed;
}