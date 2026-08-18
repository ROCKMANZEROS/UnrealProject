#include "AirFlatfrom4.h"


AAirFlatfrom4::AAirFlatfrom4()
{

	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Game/Resources/Props/SM_AssetPlatform.SM_AssetPlatform"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Metal_Gold.M_Metal_Gold"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	PrimaryActorTick.bCanEverTick = true;
	MoveSpeed = 150.0f;
	MaxRange = 400.0f;
}
void AAirFlatfrom4::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
	EndLocation = StartLocation + FVector(MaxRange, 0.0f, 0.0f);
}


void AAirFlatfrom4::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();

	CurrentLocation.X += MoveSpeed * DeltaTime;
	SetActorLocation(CurrentLocation);

	if (CurrentLocation.X >= EndLocation.X)
	{
		SetActorLocation(EndLocation);

		MoveSpeed = -MoveSpeed;
	}

	else if (MoveSpeed < 0.0f && CurrentLocation.X <= StartLocation.X)
	{
		SetActorLocation(StartLocation);

		MoveSpeed = -MoveSpeed;
	}
}

