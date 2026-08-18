#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AirFlatfrom4.generated.h"

UCLASS()
class UNREALPROJECT_API AAirFlatfrom4 : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AAirFlatfrom4();

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
