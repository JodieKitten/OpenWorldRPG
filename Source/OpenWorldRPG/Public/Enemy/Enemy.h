// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Interfaces/HitInterface.h"
#include "Characters/CharacterTypes.h"
#include "Enemy.generated.h"

class UHealthBarComponent;
class AAIController;
class UPawnSensingComponent;
class ASouls;

UCLASS()
class OPENWORLDRPG_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemy();
	virtual void Tick(float DeltaTime) override;

	/* Damage */
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter);
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Destroyed() override;


protected:
	virtual void BeginPlay() override;

	/* Attack */
	virtual void Attack() override;
	virtual bool CanAttack() override;
	virtual void AttackEnd() override;

	/* Damage */
	virtual void HandleDamage(float DamageAmount) override;
	virtual void Die_Implementation();
	void SpawnSoul();

	UPROPERTY(BlueprintReadOnly)
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;


private:
	void InitializeEnemy();

	/* Targeting */
	bool IsOutSideCombatRadius();
	void LoseInterest();
	void StartPatrolling();
	bool IsOutsideAttackRadius();
	void ChaseTarget();
	bool IsChasing();
	bool IsInsideAttackRadius();
	bool IsAttacking();
	bool IsEngaged();
	bool IsDead();
	void CheckPatrolTarget();
	void CheckCombatTarget();
	void PatrolTimerFinished();
	void ClearPatrolTimer();
	bool InTargetRange(AActor* Target, double Radius);
	void MoveToTarget(AActor* Target);
	AActor* ChoosePatrolTarget();
	UFUNCTION()
	void PawnSeen(APawn* SeenPawn);

	FTimerHandle PatrolTimer;

	UPROPERTY(EditAnywhere, Category = Combat)
	double CombatRadius = 1000.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	double AttackRadius = 130.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	double AcceptanceRadius = 50.f;

	UPROPERTY(EditAnywhere)
	double PatrolRadius = 200.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float PatrollingSpeed = 125.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float ChasingSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMin = 5.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMax = 10.f;

	/* Attack */
	void StartAttackTimer();
	void ClearAttackTimer();
	void SpawnDefaultWeapon();

	FTimerHandle AttackTimer;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMin = 0.5;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMax = 1.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float DeathLifeSpan = 8.f;

	/* Components */
	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, Category = Combat)
	TSubclassOf<class ASouls> SoulClass;

	/* Navigation */

	UPROPERTY()
	AAIController* EnemyController;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

	/* HUD */
	void HideHealthBar();
	void ShowHealthBar();
};
