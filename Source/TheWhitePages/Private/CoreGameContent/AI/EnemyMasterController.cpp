#include "CoreGameContent/AI/EnemyMasterController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"

void AEnemyMasterController::InstantiateBehaviorTree()
{
    if (BehaviorTreeAsset)
    {
        RunBehaviorTree(BehaviorTreeAsset);
        BlackboardComp = GetBlackboardComponent();
    }
    AIPerceptionComp = Cast<UAIPerceptionComponent>(GetComponentByClass(UAIPerceptionComponent::StaticClass()));
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
        BlackboardComp->SetValueAsVector(KeyNames.POIKeyName, Location);
        BlackboardComp->SetValueAsEnum(KeyNames.StateKeyName, static_cast<uint8>(EAIEnemyState::Searching));
    }
}

void AEnemyMasterController::SetStateAsSeekingTarget(const FVector& Location)
{
    if (BlackboardComp)
    {
        BlackboardComp->SetValueAsVector(KeyNames.POIKeyName, Location);
        BlackboardComp->SetValueAsEnum(KeyNames.StateKeyName, static_cast<uint8>(EAIEnemyState::SeekingTarget));
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

#pragma endregion

#pragma region "AI Detection / Perception"

void AEnemyMasterController::HandleSensedSight(AActor* Actor)
{
    if (Actor && BlackboardComp)
    {
        KnownSeenActors.AddUnique(Actor);

        EAIEnemyState CurrState;
        GetCurrentState(CurrState);

        if (CurrState == EAIEnemyState::Passive || CurrState == EAIEnemyState::Searching || CurrState == EAIEnemyState::SeekingTarget)
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

        if (CurrState == EAIEnemyState::Passive || CurrState == EAIEnemyState::Searching || CurrState == EAIEnemyState::SeekingTarget)
        {
            FVector CurrLocation = SoundLocation;
            SetStateAsSearching(CurrLocation);
        }
    }
}

void AEnemyMasterController::HandleForgottenActor(AActor* Actor)
{
    if (Actor)
    {
        KnownSeenActors.Remove(Actor);
        SetStateAsPassive();
    }
}

void AEnemyMasterController::HandleLostSight(AActor* Actor)
{
    if (Actor && BlackboardComp)
    {
        EAIEnemyState CurrState;
        GetCurrentState(CurrState);
        ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

        if (Actor == PlayerCharacter)
        {
            if (CurrState == EAIEnemyState::Aggro || CurrState == EAIEnemyState::Frozen)
            {
                FVector Location = Actor->GetActorLocation();
                SetStateAsSeekingTarget(Location);
            }
        }
    }
}

// void AEnemyMasterController::CheckForgottenSceneActor()
// {
//     if (AIPerceptionComp)
//     {
//         TArray<AActor*> CurrPerceivedActors;
//         AIPerceptionComp->GetKnownPerceivedActors(UAISense_Sight::StaticClass(), CurrPerceivedActors);

//         if (KnownSeenActors.Num() != CurrPerceivedActors.Num())
//         {
//             for (AActor* SeenActor : KnownSeenActors)
//             {
//                 if (CurrPerceivedActors.Find(SeenActor) == INDEX_NONE)
//                 {
//                     HandleForgottenActor(SeenActor);
//                 }
//             }
//         }
//     }
// }


#pragma endregion