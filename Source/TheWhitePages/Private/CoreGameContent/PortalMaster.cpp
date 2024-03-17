#include "CoreGameContent/PortalMaster.h"
#include "Components/BillboardComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/BoxComponent.h"

// Sets default values
APortalMaster::APortalMaster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PortalRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	PortalRootComponent->SetupAttachment(GetRootComponent());
	PortalFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	PortalFrame->SetupAttachment(PortalRootComponent);
	PortalPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	PortalPlane->SetupAttachment(PortalRootComponent);
	ForwardDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ForwardDirection->SetupAttachment(PortalRootComponent);
	PortalCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Camera"));
	PortalCamera->SetupAttachment(PortalRootComponent);
	PlayerDetection = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	PlayerDetection->SetupAttachment(PortalRootComponent);
}

// Called when the game starts or when spawned
void APortalMaster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APortalMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

