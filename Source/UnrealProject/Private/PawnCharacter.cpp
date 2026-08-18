#include "PawnCharacter.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"



APawnCharacter::APawnCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	//CapsuleComp->SetRootComponent(CapsuleComp);
	SetRootComponent(CapsuleComp);

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	SkeletalMeshComp->SetupAttachment(RootComponent);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CamareComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	
	CapsuleComp->SetSimulatePhysics(false);
	SkeletalMeshComp->SetSimulatePhysics(false);
	
}


void APawnCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}


void APawnCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void APawnCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent * EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->
			BindAction(MoveAction, 
			ETriggerEvent::Triggered, 
			this, 
			&APawnCharacter::Move);

		EnhancedInputComponent->
			BindAction(LookAction,
				ETriggerEvent::Triggered,
				this,
				&APawnCharacter::Look);
	}
}

void APawnCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();

		FVector ForwardDirection = FRotator(0, Rotation.Yaw, 0).Vector();
		FVector RightDirection = FRotator(0, Rotation.Yaw + 90.0f, 0).Vector();

		FVector NewLocation = GetActorLocation();

		float MoveSpeed = 500.0f;
		float DeltaTime = GetWorld()->GetDeltaSeconds();

		NewLocation += ForwardDirection * MovementVector.X * MoveSpeed * DeltaTime;
		NewLocation += RightDirection * MovementVector.Y * MoveSpeed * DeltaTime;

		SetActorLocation(NewLocation);
	}
}

void APawnCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);

		if (SpringArmComp)
		{
			SpringArmComp->bUsePawnControlRotation = true;
		}
	}
}