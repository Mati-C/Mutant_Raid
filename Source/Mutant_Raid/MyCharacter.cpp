// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	armor = 0;
	life = maxLife;
	currentWeapon = 0;
	weaponTimer = 0;
	weaponsCollected = 1;
	weaponBullets = weaponMaxBullets;
	baseMaxSpeed = GetCharacterMovement()->MaxWalkSpeed;
	baseFireRate = weaponFireRate;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	weaponTimer -= DeltaTime;
	powerUpCurrentTime -= DeltaTime;
	bossMessageTimer -= DeltaTime;
	if (powerUpCurrentTime <= 0)
		PowerUpOff(powerUpActive);
	if (powerUpActive == 5)
		life -= DeltaTime * poisonAmount;
	Shoot();
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("ChangeWeapon", this, &AMyCharacter::SwitchWeapon);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMyCharacter::StartShooting);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AMyCharacter::StopShooting);
}

void AMyCharacter::PowerUpOn(int id)
{
	if (id == 0 || id == powerUpActive) return;

	powerUpActive = id;
	powerUpCurrentTime = powerUpTime;

	if (id == 1)
		damageModifier = 4;
	else if (id == 2) {
		GetCharacterMovement()->MaxWalkSpeed = baseMaxSpeed * 1.75f;
		for (int i = 0; i < weaponFireRate.Num(); i++)
			weaponFireRate[i] = baseFireRate[i] / 1.5f;
	}
	else if (id == 4) {
		GetCharacterMovement()->MaxWalkSpeed = baseMaxSpeed / 1.75f;
		for (int i = 0; i < weaponFireRate.Num(); i++)
			weaponFireRate[i] = baseFireRate[i] * 1.5f;
	}
}

void AMyCharacter::PowerUpOff(int id)
{
	powerUpActive = 0;

	if (id == 1)
		damageModifier = 1;
	else if (id == 2 || id == 4) {
		GetCharacterMovement()->MaxWalkSpeed = baseMaxSpeed;
		for (int i = 0; i < weaponFireRate.Num(); i++)
			weaponFireRate[i] = baseFireRate[i];
	}
}

void AMyCharacter::StartShooting()
{
	isShooting = true;
}

void AMyCharacter::StopShooting()
{
	isShooting = false;
}

void AMyCharacter::Damage(float dmg)
{
	if (powerUpActive == 3) {
		playerAudio->SetSound(playerInvulnerable);
		playerAudio->Play();
		return;
	}

	playerAudio->SetSound(playerHit);
	playerAudio->Play();

	armor -= dmg;
	life = armor < 0 ? life + armor : life;
	armor = armor < 0 ? 0 : armor;
}

void AMyCharacter::SwitchWeapon(float val)
{
	currentWeapon += (int)val;

	if (currentWeapon == -1)
		currentWeapon = weaponsCollected;
	else if (currentWeapon == weaponsCollected + 1)
		currentWeapon = 0;

	weapon->SetSkeletalMesh(weaponMeshes[currentWeapon]);
	weapon->SetRelativeTransform(weaponTransforms[currentWeapon]);
}

void AMyCharacter::Shoot()
{
	if (!isShooting || weaponTimer > 0) return;

	weaponTimer = weaponFireRate[currentWeapon];

	if (weaponBullets[currentWeapon] == 0) {
		gunAudio->SetSound(weaponEmpty);
		gunAudio->Play();
		return;
	}

	if (currentWeapon == 1)
	{
		for (int i = 0; i <= shotgunPellets; i++)
		{
			FRotator rot = weaponPH->GetComponentRotation();
			rot.Yaw += FMath::FRandRange(-shotgunSpread, shotgunSpread);
			rot.Roll += FMath::FRandRange(-shotgunSpread, shotgunSpread);
			GetWorld()->SpawnActor<AActor>(bullet, weaponPH->GetComponentLocation(), rot, FActorSpawnParameters());
		}
	}
	else if (currentWeapon == 2)
		GetWorld()->SpawnActor<AActor>(grenade, weaponPH->GetComponentLocation(), weaponPH->GetComponentRotation(), FActorSpawnParameters());
	else
		GetWorld()->SpawnActor<AActor>(bullet, weaponPH->GetComponentLocation(), weaponPH->GetComponentRotation(), FActorSpawnParameters());

	gunAudio->SetSound(weaponSounds[currentWeapon]);
	gunAudio->Play();

	float animSpeed = currentWeapon == 0 ? 1 : 0.5f;
	animSpeed *= powerUpActive == 2 ? 1.5f : 1;
	arms->GetAnimInstance()->Montage_Play(montage, animSpeed);
	weaponBullets[currentWeapon]--;
}

