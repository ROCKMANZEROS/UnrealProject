#include "AirFlatfrom2.h"


AAirFlatfrom2::AAirFlatfrom2()
{
	
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_AssetPlatform.SM_AssetPlatform"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Wood_Oak.M_Wood_Oak"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}


	PrimaryActorTick.bCanEverTick = true;
	MoveSpeed = 100.0f;
	MaxRange = 180.0;
}


void AAirFlatfrom2::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();

	EndLocation = StartLocation;
	EndLocation.Z += MaxRange;

}


void AAirFlatfrom2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();

	CurrentLocation.Z += MoveSpeed * DeltaTime;
	SetActorLocation(CurrentLocation);

	if (CurrentLocation.Z >= EndLocation.Z)
	{
		SetActorLocation(EndLocation);

		MoveSpeed = -MoveSpeed;
	}

	else if (MoveSpeed < 0.0f && CurrentLocation.Z <= StartLocation.Z)
	{
		SetActorLocation(StartLocation);

		MoveSpeed = -MoveSpeed;
	}
}

