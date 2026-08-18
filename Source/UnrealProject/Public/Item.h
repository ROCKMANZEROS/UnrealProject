#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"          // 리플렉션 시스템을 포함한 헤더파일 (항상 #include 중 제일 밑에 있어야 된다!!!!!!)


UCLASS()     //Blueprintable, BlueprintType 를 ()안에 안적어도 적은 것과 같은 내용
             // BlueprintType 만 사용하면 상속은 불가능해짐 (주의!) 꼭 둘 다 적거나 안적거나
class UNREALPROJECT_API AItem : public AActor
{
	GENERATED_BODY()          // UCLASS()와 항상 세트인 녀석
	
public:	
	AItem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Item|Components")
	            // ㄴ 수정 불가        ㄴ 블루프린트 노드 얘기 (읽기만 가능 set X, get만 가능)
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Components")
	            // ㄴ 클래스 디폴트, 인스턴스 수정 다 가능
	                              // ㄴ get, set 둘 다 가능
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item|Components")
	            // ㄴ 디폴트에서만 수정 가능
	            // EditInstanceOnly = 인스턴스에서만 수정 가능
	float RotationSpeed;

	//virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	//virtual void Destroyed() override;
	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;*/

	UFUNCTION(BlueprintCallable, Category="Item|Actions")
	           // ㄴ 블루프린트에서 호출 가능하게 하는 함수
	void ResetActorPostion();

	UFUNCTION(BlueprintPure, Category="Item|Properties")
	           // ㄴ 블루프린트에서 값(리턴 값만) 반환 받을 수 있다. 실행 핀 X
	float GetRotationSpeed() const;

	UFUNCTION(BlueprintImplementableEvent, Category="Item|Event")
	           // ㄴ 블루프린트에서 구현하고 C++에서도 호출 가능하게 함!
	void OnItemPickedUP();
	
};

