#include "ShooterCharacter.h"

#include "Health/HealthComponent.h"
#include "AI/ShooterAIController.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameModes/ShooterGameMode.h"

void AShooterCharacter::OnFireHit(FVector ImpactPoint, AActor* Actor)
{
	if (OnBulletHit.IsBound())
		OnBulletHit.Broadcast(ImpactPoint, Actor);

	if (!Actor)
		return;

	const auto Character = Cast<AShooterCharacter>(Actor);

	if (!Character)
		return;

	const auto Event = FDamageEvent();

	Character->TakeDamage(
		WeaponDamage,
		Event,
		GetController(),
		this
	);
}

void AShooterCharacter::HandleDeath(AActor* Source)
{
	AController* ActorController = GetController();
	TSubclassOf<APawn> PawnClass = GetClass();

	if (ActorController)
		ActorController->UnPossess();

	const auto World = GetWorld();
	check(World);

	const auto GameMode = Cast<AShooterGameMode>(World->GetAuthGameMode());

	if (GameMode)
		GameMode->HandleDeath(ActorController, PawnClass);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
                                    AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (ActualDamage > 0.0f)
	{
		CurrentHealth = FMath::Max(0.0f, CurrentHealth - ActualDamage);

		if (CurrentHealth <= 0.0f)
		{
			// Is dead should respawn 
			return 0.0f;
		}

		AShooterAIController* AIController = Cast<AShooterAIController>(GetController());

		if (!AIController)
			return ActualDamage;

		AIController->IsGettingAttacked(DamageCauser);
	}
	return ActualDamage;
}

AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	WalkSpeed = 500;
	AimedWalkSpeed = 200;

	WeaponDamage = 1.0f;
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	const auto Health = FindComponentByClass<UHealthComponent>();

	if (Health)
		Health->OnDeath.AddDynamic(this, &AShooterCharacter::HandleDeath);
}

void AShooterCharacter::DoStartAim()
{
	if (bIsAiming)
		return;

	bIsAiming = true;

	const auto Movement = GetCharacterMovement();

	if (Movement)
		Movement->MaxWalkSpeed = AimedWalkSpeed;
}

void AShooterCharacter::DoEndAim()
{
	if (!bIsAiming)
		return;

	bIsAiming = false;

	const auto Movement = GetCharacterMovement();

	if (Movement)
		Movement->MaxWalkSpeed = WalkSpeed;
}

void AShooterCharacter::DoFire(FVector StartLocation, FVector EndLocation)
{
	if (!bIsAiming)
		return;

	const auto World = GetWorld();
	check(World);

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
		StartLocation,
		EndLocation,
		ECC_WorldDynamic,
		Params
	);

	if (!bHit || !Hit.bBlockingHit)
		return;

	const auto Actor = Hit.GetActor();

	OnFireHit(Hit.ImpactPoint, Actor);
}
