#include "CoreGameContent/AI/EnemyMasterController.h"
#include "BehaviorTree/BlackboardComponent.h"


void AEnemyMasterController::InstantiateBehaviorTree()
{
    if (BehaviorTreeAsset)
    {
        RunBehaviorTree(BehaviorTreeAsset);
        BlackboardComp = GetBlackboardComponent();
    }
}

void AEnemyMasterController::SetStateAsPassive()
{
    if (BlackboardComp)
    {
        BlackboardComp->SetValueAsEnum(StateKeyName, static_cast<uint8>(EAIEnemyState::Passive));
    }
}

void AEnemyMasterController::SetStateAsAttacking(AActor* AttackTarget)
{
    if (AttackTarget != nullptr && BlackboardComp)
    {
        BlackboardComp->SetValueAsObject(TargetKeyName, AttackTarget);
        BlackboardComp->SetValueAsEnum(StateKeyName, static_cast<uint8>(EAIEnemyState::Aggro));
    }
}