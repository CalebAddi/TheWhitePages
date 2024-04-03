#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyMaster.generated.h"

UCLASS()
class THEWHITEPAGES_API AEnemyMaster : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	class USkeletalMeshComponent* EnemyMesh;

public:
	// Sets default values for this character's properties
	AEnemyMaster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
