#pragma once

#include "CoreMinimal.h"
#include "ItemSpawnRow.generated.h"

USTRUCT(BlueprintType)
struct FItemSpawnRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ItemClass;
	// ㄴ 하드 레퍼런스란? 클래스가 항상 메모리에 로드된 상태에서 바로 접근.
	 // ㄴ 반대는 TSoftClassPtr - 소프트 레퍼런스란? 클래스의 경로만 유지.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnChance;
};
