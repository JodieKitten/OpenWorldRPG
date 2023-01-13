// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "CharacterTypes.h"
#include "Interfaces/PickupInterface.h"
#include "SlashCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class AItem;
class UAnimMontage;
class USlashOverlay;
class ASouls;
class ATreasure;

UCLASS()
class OPENWORLDRPG_API ASlashCharacter : public ABaseCharacter, public IPickupInterface
{
	GENERATED_BODY()

public:
	ASlashCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;
	virtual void SetOverlappingItem(class AItem* Item) override;

	/* Attributes */
	virtual void AddSouls(ASouls* Souls) override;
	virtual void AddGold(ATreasure* Treasure) override;


	/* Damage */
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter);
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;
	virtual void Die_Implementation();

	/* Input functions */
	void MoveForward(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void MoveRight(float Value);
	void EKeyPressed();
	void Dodge();

	/* Attributes */
	bool HasEnoughStamina();

	/* States */
	bool IsOccupied();

	/* Equip functions */
	void EquipWeapon(AWeapon* Weapon);
	bool CanDisarm();
	void Arm();
	bool CanArm();
	void Disarm();

	UFUNCTION(BlueprintCallable)
	void AttachWeaponToBack();

	UFUNCTION(BlueprintCallable)
	void AttachWeaponToHand();

	UFUNCTION(BlueprintCallable)
	void FinishEquipping();

	UFUNCTION(BlueprintCallable)
	void HitReactEnd();

	/* Attack functions */
	virtual void AttackEnd() override;
	virtual bool CanAttack() override;
	virtual void Attack() override;
	virtual void DodgeEnd() override;

	/* Play montage functions */
	void PlayEquipMontage(const FName& SectionName);

private:
	/* HUD */
	void InitializeSlashOverlay();
	void SetHUDHealth();

	UPROPERTY()
	USlashOverlay* SlashOverlay;

	/* Components */
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Hair;

	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Eyebrows;

	/* Weapons */
	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

	/* Animation montages */
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* EquipMontage;

	/* States */
	bool IsUnoccupied();

	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;

public:
	FORCEINLINE ECharacterState GetCharacterState() { return CharacterState; }
	FORCEINLINE EActionState GetActionState() const { return ActionState; }
};
