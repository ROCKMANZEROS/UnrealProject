#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AirFlatfrom3.generated.h"

UCLASS()
class UNREALPROJECT_API AAirFlatfrom3 : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AAirFlatfrom3();

protected:

	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platfrom")
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platfrom")
	int MaxRange;

	FVector StartLocation;
	FVector EndLocation;

	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

};
