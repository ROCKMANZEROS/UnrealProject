#include "Item.h"



// Sets default values
AItem::AItem()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	/*static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Chair.SM_Chair"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Metal_Gold.M_Metal_Gold"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	PrimaryActorTick.bCanEverTick = true;   // -> Tick 함수는 켜줘야하고 안쓰면 false로 해놔야됨.
	RotationSpeed = 90.0f;   */   //-> StaticMeshComp를 EditAnyWhere로 했기 떄문에 여기서 설정해주지 않아도 됨!
	
}



void AItem::BeginPlay()
{
	Super::BeginPlay();

	/* SetActorLocation(FVector(300.0f, 200.0f, 100.0f));
	SetActorRotation(FRotator(0.0f, 90.0f, 0.0f)); //  ->  짐벌락 문제?  대체제인 회전값을 나타내는 FQuat 이 있음.
	                      // pitch , yaw,  roll
						  //  y축     z축   x축
	SetActorScale3D(FVector(2.0f, 1.0f, 1.0f)); */
	                      // 전체 2배면 (2.0f) 하나만 해도 가능

	/*FVector NewLocation(300.0f, 200.0f, 100.0f);
	FRotator NewRotation(0.0f, 90.0f, 0.0f);
	FVector NewScale(2.0f);

	FTransform NewTransform(NewRotation, NewLocation,  NewScale); // -> 로테이션이 먼저
	//ㄴFTransform으로 한번에 바꾸 수도 있다.
	SetActorTransform(NewTransform);*/

	//UE_LOG(LogTemp, Warning, TEXT("My Log!"));
	//UE_LOG(LogSparta, Error, TEXT("My Sparta"));
	//UE_LOG(LogSparta, Warning, TEXT("%s BeginPlay"), *GetName());

	OnItemPickedUP();
}

void AItem::Tick(float DeltaTime)
{                         // ㄴ 프레임 당 시간
	// 120 프레임 - 1초에 120번 호출, 1초 / 120 = DeltaTime
	// 30 프레임 - 1초에 30번 호출, 1초 / 30 = DeltaTime
	// 1초에 90도씩 회전
	// 90도 / 120 = 0.0005
	// 90도 / 30 = 0.01
	// 1초 = 90도 회전
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	}

	

}

// 라이플 사이클 함수
// ------탄생--------
// ㄴ 생성자 - 메모리에 생김. 딱 한 번 호출.
// PostInitializeComponents() - 컴포넌트가 완성된 직후 호출. 컴포넌트끼리 데이터 주고받기, 상호작용.
// BeginPlay() - 배치 (Spawn) 직후.
// ------죽음---------
// Tick(float DeltaTime) - 매 프레임마다 호출된.
// Distoyed() - 외부에서 강제 삭제. 삭제 되기 직전에 호출. -> D 를 호출하면 E도 호출됨
// EndPlay() - 게임 종료, 파괴 (Distroyed()), 레벨 전환.

void AItem::ResetActorPostion()
{
SetActorLocation(FVector::ZeroVector);
                            // ㄴ 해당 FVector값이 원점을 의미
}

float AItem::GetRotationSpeed() const
{
	return RotationSpeed;
}
