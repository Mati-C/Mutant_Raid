// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class MUTANT_RAID_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(BlueprintReadWrite)
		USkeletalMeshComponent* arms;
	UPROPERTY(EditAnywhere)
		UAnimMontage* montage;

	UPROPERTY(BlueprintReadWrite)
		USkeletalMeshComponent* weapon;
	UPROPERTY(BlueprintReadWrite)
		USphereComponent* weaponPH;
	UPROPERTY(EditAnywhere)
		TArray<USkeletalMesh*> weaponMeshes;
	UPROPERTY(EditAnywhere)
		TArray<FTransform> weaponTransforms;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<float> weaponFireRate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<float> baseFireRate;
	UPROPERTY(EditAnywhere)
		TArray<USoundBase*> weaponSounds;
	UPROPERTY(EditAnywhere)
		USoundBase* weaponEmpty;
	UPROPERTY(EditAnywhere)
		USoundBase* playerHit;
	UPROPERTY(EditAnywhere)
		USoundBase* playerInvulnerable;
	UPROPERTY(BlueprintReadWrite)
		TArray<int> weaponBullets;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<int> weaponMaxBullets;
	UPROPERTY(BlueprintReadOnly)
		int currentWeapon;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> bullet;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> grenade;
	int weaponsCollected;
	float weaponTimer;
	bool isShooting;
	UPROPERTY(EditAnywhere)
		int shotgunPellets;
	UPROPERTY(EditAnywhere)
		float shotgunSpread;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float maxLife;
	UPROPERTY(BlueprintReadWrite)
		float life;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float maxArmor;
	UPROPERTY(BlueprintReadWrite)
		float armor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float damageModifier;
	UPROPERTY(EditAnywhere)
		float poisonAmount;

	UPROPERTY(BlueprintReadOnly)
		int powerUpActive;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float powerUpTime;
	UPROPERTY(BlueprintReadOnly)
		float powerUpCurrentTime;

	UFUNCTION(BlueprintCallable)
		void PowerUpOn(int id);
	void PowerUpOff(int id);
	UFUNCTION(BlueprintCallable)
		void Damage(float dmg);
	void SwitchWeapon(float val);
	void Shoot();
	void StartShooting();
	void StopShooting();

	UPROPERTY(BlueprintReadWrite)
		UAudioComponent* gunAudio;
	UPROPERTY(BlueprintReadWrite)
		UAudioComponent* playerAudio;

	UPROPERTY(BlueprintReadWrite)
		bool isFightingBoss;
	UPROPERTY(BlueprintReadWrite)
		float bossLife;
	UPROPERTY(BlueprintReadOnly)
		float bossMessageTimer;
	UPROPERTY(BlueprintReadWrite)
		int mutantsRemaining;
	UPROPERTY(BlueprintReadWrite)
		int mutantsToSpawn;

	float baseMaxSpeed;
};
