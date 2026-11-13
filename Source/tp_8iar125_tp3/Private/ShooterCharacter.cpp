#include "ShooterCharacter.h"

#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"

void AShooterCharacter::OnFireHit(FVector ImpactPoint, AActor* Actor)
{
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
	//GetHealthComponent()->TakeDamage(1.0f,this);
}

AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	WalkSpeed = 500;
	AimedWalkSpeed = 200;

	WeaponDamage = 1.0f;
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
