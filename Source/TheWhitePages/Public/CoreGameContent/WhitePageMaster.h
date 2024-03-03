#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WhitePageMaster.generated.h"

UCLASS()
class THEWHITEPAGES_API AWhitePageMaster : public AActor
{
	GENERATED_BODY()
	
public:	
	AWhitePageMaster();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:	
	

};
