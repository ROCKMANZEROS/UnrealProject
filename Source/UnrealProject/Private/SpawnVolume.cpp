#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"


ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);

	ItemDataTable = nullptr;
}

AActor* ASpawnVolume::SpawnRandomItem()
{
	if (FItemSpawnRow* SelectedRow = GetRandomItem())
	{
		if (UClass* ActualClass = SelectedRow->ItemClass.Get())
		{
			return SpawnItem(ActualClass);
		}
	}

	return nullptr;
}

FItemSpawnRow* ASpawnVolume::GetRandomItem() const
{
	if (!ItemDataTable) return nullptr;
	
	TArray<FItemSpawnRow*> AllRows;
	static const FString ContextString(TEXT("ItemSpawnContext"));

	ItemDataTable->GetAllRows(ContextString, AllRows);

	if (AllRows.IsEmpty()) return nullptr;

	float TotalChance = 0.0f;
	for (const FItemSpawnRow* Row : AllRows)
	{
		if (Row)
		{
			TotalChance += Row->SpawnChance;
		}
	}

	const float RandValue = FMath::FRandRange(0.0f, TotalChance);
	float AccumulateChance = 0.0f;
	// ex1: 0.0 ~ 1.0 에서 0.7이면  Item A 0.5 / Item B 0.7 / Item C 1.0 일때 Item B 가 나옴   <- 누적확률로 뽑는다.
	// ex2: 빨간공 5개(50%), 파란공 3개(30%), 초록공 2개(20%) 일때 전체 10개 ,0~1까지 랜덤 숫자를 뽑아 0.1이면 빨간공, 0.6이면 파란공, 0.9면 초록공이 뽑힌다.

	for (FItemSpawnRow* Row : AllRows)
	{
		AccumulateChance += Row->SpawnChance;
		if (RandValue <= AccumulateChance)
		{
			return Row;
		}
	}

	return nullptr;
}

	FVector ASpawnVolume::GetRandomPointInVloume() const
	{
		FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
			                                  // ㄴ 박스에 반지름 값 반환 (Extent = 중심에서 끝부분까지)
		FVector BoxOrigin = SpawningBox->GetComponentLocation();

		return BoxOrigin + FVector(
			FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
			FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
			FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
		);
	}

	AActor* ASpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass)
	{
		if (!ItemClass) nullptr;

		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
			ItemClass,
			GetRandomPointInVloume(),
			FRotator::ZeroRotator
		);

		return SpawnedActor;
	}



