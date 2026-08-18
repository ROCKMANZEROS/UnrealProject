#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpartaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWidgetComponent;
struct FInputActionValue;

// UI - 스크린 모드 = 카메라 상관없이 항상 정면에 띄움
// UI - 월드 모드 = 월드 캐릭터에 움직임에 따라 글씨도 움직임 

UCLASS()
class UNREALPROJECT_API ASpartaCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ASpartaCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* OverheadWidget;

	UFUNCTION(BlueprintPure, Category = "health")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddHealth(float Amount);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "health")
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "health")
	float Health;

	virtual void BeginPlay() override;
	// virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,      // 나중에 속성 공격(스킬) 구현할 때 사용한다!
		AController* EventInstigator,                // EventInstigator는 데미지를 구가 입혔는지, 상대 또는 몬스터 / 지금은 null값, 지뢰를 심은 사람 느낌~
		AActor* DamageCauser) override;

	UFUNCTION()
	void Move(const FInputActionValue& value);         // 구조체는 크기 떄문에 직접 가져오면 모든 객체 데이터를 가져와 무거워진자. 참조를 하자 (const 는 수정 금지)
	UFUNCTION()
	void StartJump(const FInputActionValue& value);    // 점프를 눌렀을 때와 땠을 때를 나눠주는게 좋다.
	UFUNCTION()
	void StopJump(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void StartSprint(const FInputActionValue& value);
	UFUNCTION()
	void StopSprint(const FInputActionValue& value);

	void OnDeath();
	void UpdateOverheadHP();


private:
	float NormalSpeed;
	float SprintSpeedMultiplier;
	float SprintSpeed;
};
