#pragma once

#include "CoreMinimal.h"
#include "Actor/Weapon/AttachmentData.h"
#include "Actor/Weapon/WeaponData.h"
#include "ActorComponents/Inventory/InventoryData.h"
#include "Engine/DataTable.h"
#include "ItemData.generated.h"

class UAttachmentComponent;
class AWeapon;

UENUM(BlueprintType)
enum class EItemCondition : uint8
{
	EIC_Pristine UMETA(DisplayName="Pristine"),
	EIC_Worn UMETA(DisplayName="Worn"),
	EIC_Damaged UMETA(DisplayName="Damaged"),
	EIC_BadlyDamaged UMETA(DisplayName="BadlyDamaged"),
	EIC_Ruined UMETA(DisplayName="Ruined")
};

// Functionality inside the inventory grid, can they equip, do they attach, can they consume, does it hold more inside
UENUM(BlueprintType)
enum class EItemType : uint8
{
	EIT_Weapon UMETA(DisplayName="Weapon"),
	EIT_Armor UMETA(DisplayName="Armor"),
	EIT_Ammunition UMETA(DisplayName="Ammunition"),
	EIT_Container UMETA(DisplayName="Container"),
	EIT_Attachment UMETA(DisplayName="Attachment"),
	EIT_Consumable UMETA(DisplayName="Consumable"),
	EIT_Material UMETA(DisplayName="Material"),
	EIT_Misc UMETA(DisplayName="Misc"),
};

USTRUCT(BlueprintType)
struct FContainerData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 CurrentCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 MaxCapacity = 0;
};

USTRUCT(BlueprintType)
struct FItemTextData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Name = FText::GetEmpty();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Description = FText::GetEmpty();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Interaction = FText::GetEmpty();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Usage = FText::GetEmpty();
};

USTRUCT(BlueprintType)
struct FItemStatistics 
{
	GENERATED_BODY()
	
	//~ Damage
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float FireInterval = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float HealthDamage = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float HardDamage = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float BloodLoss = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float DropoffRange = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float MinDamageRange = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float MaxRange = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float AccuracyRadiusAt10m = 0.f;
	
	//~ Aiming
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float PerShotModifier = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float ShotModifierCap = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float RecoveryDelay = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float RecoveryPerSecond = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float GravityModifier = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float CrouchModifier = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float WalkModifier = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float RunModifier = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float SprintModifier = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float JumpModifier = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float LeanModifier = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float MarksmanModifier = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float InVehicleModifier = 0.f;

	//~ Movement

	//~ Ammo
	
	//~ Inventory
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float Value = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float SellValue = 0.f;
};

USTRUCT(BlueprintType)
struct FItemNumericData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 GridWidth = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 GridHeight = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float Weight = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 MaxStackSize = 0;
	UPROPERTY(BlueprintReadOnly) bool bIsStackable = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 MaxCharges = 0;
	UPROPERTY(BlueprintReadOnly) bool bHasCharges = false;
};

USTRUCT(BlueprintType, Blueprintable)
struct FItemAssetData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item") TObjectPtr<UTexture2D> Icon = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item") TObjectPtr<UMaterialInterface> SpatialIcon = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item") TObjectPtr<UMaterialInterface> SpatialIconRotated = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item") TObjectPtr<UStaticMesh> Mesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item") TObjectPtr<USkeletalMesh> ItemSkeletalMesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item") TObjectPtr<USoundBase> PickupSound = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon") TSubclassOf<AWeapon> WeaponClass = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon") TMap<EAttachmentType, FAttachmentData> WeaponAttachmentsMap;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon") EAmmoContainerType AmmoContainerType = EAmmoContainerType::EACT_Internal;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon") int32 InternalMaxCapacity = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attachment") TSubclassOf<UAttachmentComponent> AttachmentComponentClass = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attachment") FAttachmentData AttachmentComponentData;
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Data") FName ID = FName();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Data") FItemTextData TextData = FItemTextData();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Data") ESlotType SlotType = ESlotType::EIT_Inventory;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Data") EItemType ItemType = EItemType::EIT_Misc;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Data") EItemCondition ItemCondition = EItemCondition::EIC_Pristine;
	
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Data|Container") FContainerData ContainerData = FContainerData();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Data|Container") EAmmunitionType AmmunitionType = EAmmunitionType::EAT_9x19mm;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Data") FItemAssetData AssetData = FItemAssetData();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Data") FItemNumericData NumericData = FItemNumericData();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Data") FItemStatistics ItemStatistics = FItemStatistics();
};