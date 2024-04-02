#include "CoreGameContent/AI/EnemyMaster.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AEnemyMaster::AEnemyMaster()
{
	PrimaryActorTick.bCanEverTick = true;

	EnemyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Enemy"));
	EnemyMesh->SetupAttachment(GetRootComponent());
}

void AEnemyMaster::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AEnemyMaster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

