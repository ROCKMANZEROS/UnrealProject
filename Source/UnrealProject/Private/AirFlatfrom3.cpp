#include "AirFlatfrom3.h"


AAirFlatfrom3::AAirFlatfrom3()
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

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT(""));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}


	PrimaryActorTick.bCanEverTick = true;
	MoveSpeed = 150.0f;
	MaxRange = 400.0f;
}

void AAirFlatfrom3::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	EndLocation = StartLocation + FVector(0.0f, MaxRange, 0.0f);
	
}


void AAirFlatfrom3::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();

	CurrentLocation.Y += MoveSpeed * DeltaTime;
	SetActorLocation(CurrentLocation);

	if (CurrentLocation.Y >= EndLocation.Y)
	{
		SetActorLocation(EndLocation);

		MoveSpeed = -MoveSpeed;
	}

	else if (MoveSpeed < 0.0f && CurrentLocation.Y <= StartLocation.Y)
	{
		SetActorLocation(StartLocation);

		MoveSpeed = -MoveSpeed;
	}
}