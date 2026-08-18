#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"


UINTERFACE(MinimalAPI)                    // <- UItemInterface 는 건들필요 없음
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

class UNREALPROJECT_API IItemInterface
{
	GENERATED_BODY()

	
public:
	UFUNCTION()
	virtual void OnItemOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) = 0;     // 몬스터, 투사체, 드론 등 뭐가 지나갈지 모르니 Actor로 하자

	UFUNCTION()
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) = 0;              // 0을 안붙치면 무조건 오버라이딩을 해야됨. (이렇게 만드는게 순수가상함수다.)

	virtual void ActivateItem(AActor* Activator) = 0;
	virtual FName GetItemType() const = 0;                         // 타입형을 알아낼 때 속도가 너 빠르다. string은 의외로 무거움

	//힐링, 코인 - 즉시 발동형 - 오버랩
	//지뢰 - 범위 내에 오버랩 - 발동이 5초뒤 폭발 - 오버랩 - 데미지

};
