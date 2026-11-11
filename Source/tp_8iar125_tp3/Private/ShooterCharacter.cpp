#include "tp_8iar125_tp3/Public/ShooterCharacter.h"

#include "AI/ShooterAIController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/HealthComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

void AShooterCharacter::SetAiming(const bool bSetAiming)
{
	if (IsAiming == bSetAiming)
		return;
	
	IsAiming = bSetAiming;
	SetAiming(bSetAiming);
}

AShooterCharacter::AShooterCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create SK_Gun
	SK_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	SK_Gun->SetupAttachment(GetMesh());
	// Set parent socket
	SK_Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GripPoint"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	
	StimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	StimuliSource->RegisterWithPerceptionSystem();
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

//////////////////////////////////////////////////////////////////////////
// Input

void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AShooterCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AShooterCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AShooterCharacter::LookUpAtRate);

	// Aiming 
	PlayerInputComponent->BindAction("Aiming", IE_Pressed, this, &AShooterCharacter::Aim);
	PlayerInputComponent->BindAction("Aiming", IE_Released, this, &AShooterCharacter::StopAiming);

	// Fire
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AShooterCharacter::Fire);
}

void AShooterCharacter::Aim()
{
	SetAiming(true);
	GetCharacterMovement()->MaxWalkSpeed = 200;
}

void AShooterCharacter::StopAiming()
{
	SetAiming(false);
	GetCharacterMovement()->MaxWalkSpeed = 500;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AShooterCharacter::Fire()
{
	if (!IsAiming)
		return;

	const auto World = GetWorld();
	check(World);
	check(FollowCamera);

	const auto Start = FollowCamera->GetComponentLocation();
	const auto ForwardVector = FollowCamera->GetForwardVector();
	const auto End = Start + ForwardVector * 10000;

	FCollisionQueryParams Params = FCollisionQueryParams(
		FName(TEXT("FireTrace")),
		true,
		this
	);

	Params.bTraceComplex = true;
	Params.bReturnPhysicalMaterial = false;

	FHitResult Hit(ForceInit);

	const auto bHit = World->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_WorldDynamic,
		Params
	);

	if (!bHit || !Hit.bBlockingHit)
		return;

	SpawnImpactParticle(Hit.ImpactPoint);
	
	if (!Hit.GetActor())
		return;
	
	if (AShooterCharacter* Character =  Cast<AShooterCharacter>(Hit.GetActor()))
	{
		Character->GetHealthComponent()->TakeDamage(1.0f,this);
	}
}

void AShooterCharacter::SpawnImpactParticle(const FVector& Location) const
{
	if (!ParticleImpact)
		return;

	const auto World = GetWorld();
	check(World);

	FTransform ParticleT;
	ParticleT.SetScale3D(FVector(0.25, 0.25, 0.25));
	ParticleT.SetLocation(Location);

	UGameplayStatics::SpawnEmitterAtLocation(World, ParticleImpact, ParticleT, true);
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//HealthComponent->OnDamageTaken.AddDynamic(this,&AShooterCharacter::UpdateBehavior);
	
	if (AShooterAIController* ShooterAIController = Cast<AShooterAIController>(GetController()))
	{
		HealthComponent->OnDamageTaken.AddDynamic(ShooterAIController,&AShooterAIController::OnGettingAttacked);
	}
}

void AShooterCharacter::TurnAtRate(const float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookUpAtRate(const float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::MoveForward(const float Value)
{
	if (Value == 0.0f)
		return;

	check(Controller);

	// find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AShooterCharacter::MoveRight(const float Value)
{
	if (Value == 0.0f)
		return;

	check(Controller);

	// find out which way is right
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get right vector 
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}
