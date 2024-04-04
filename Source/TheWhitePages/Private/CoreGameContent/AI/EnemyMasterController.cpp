#include "CoreGameContent/AI/EnemyMasterController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"


void AEnemyMasterController::InstantiateBehaviorTree()
{
    if (BehaviorTreeAsset)
    {
        RunBehaviorTree(BehaviorTreeAsset);
        BlackboardComp = GetBlackboardComponent();
    }
}

#pragma region "AI States"

void AEnemyMasterController::SetStateAsPassive()
{
    if (BlackboardComp)
    {
        BlackboardComp->SetValueAsEnum(KeyNames.StateKeyName, static_cast<uint8>(EAIEnemyState::Passive));
    }
}

void AEnemyMasterController::SetStateAsSearching(const FVector& Location)
{
    if (BlackboardComp)
    {
        BlackboardComp->SetValueAsEnum(KeyNames.StateKeyName, static_cast<uint8>(EAIEnemyState::Searching));
        BlackboardComp->SetValueAsVector(KeyNames.POIKeyName, Location);
    }
}

void AEnemyMasterController::SetStateAsAttacking(AActor* AttackTarget)
{
    if (AttackTarget != nullptr && BlackboardComp)
    {
        BlackboardComp->SetValueAsObject(KeyNames.TargetKeyName, AttackTarget);
        BlackboardComp->SetValueAsEnum(KeyNames.StateKeyName, static_cast<uint8>(EAIEnemyState::Aggro));
    }
}

void AEnemyMasterController::GetCurrentState(EAIEnemyState& State) const
{
    uint8 Value = BlackboardComp->GetValueAsEnum(KeyNames.StateKeyName);
    State = static_cast<EAIEnemyState>(Value);
}

void AEnemyMasterController::HandleSensedSight(AActor* Actor)
{
    if (Actor && BlackboardComp)
    {
        EAIEnemyState CurrState;
        GetCurrentState(CurrState);

        if (CurrState == EAIEnemyState::Passive || CurrState == EAIEnemyState::Searching)
        {
            ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
            
            if (Actor == PlayerCharacter)
            {
                SetStateAsAttacking(Actor);
            }
        }
    }
}

void AEnemyMasterController::HandleSensedSound(const FVector& SoundLocation)
{
    if (BlackboardComp)
    {
        EAIEnemyState CurrState;
        GetCurrentState(CurrState);

        if (CurrState == EAIEnemyState::Passive || CurrState == EAIEnemyState::Searching)
        {
            FVector CurrLocation = SoundLocation;
            SetStateAsSearching(CurrLocation);
        }
    }
}

#pragma endregion