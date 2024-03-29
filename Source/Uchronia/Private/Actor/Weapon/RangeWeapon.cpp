// Retropsis @ 2023-2024

#include "Actor/Weapon/RangeWeapon.h"
#include "Actor/Weapon/AmmoContainer.h"
#include "Actor/Weapon/Casing.h"
#include "ActorComponents/CombatComponent.h"
#include "Character/PlayerCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/CharacterPlayerController.h"

ARangeWeapon::ARangeWeapon()
{
	// AmmoContainer = CreateDefaultSubobject<UAmmoContainer>(TEXT("AmmoContainer"));
	// AmmoContainer->SetupAttachment(WeaponMesh);
	// AmmoContainer->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	// const USkeletalMeshSocket* ClipSocket =WeaponMesh->GetSocketByName(FName("ClipSocket"));
	// if(ClipSocket)
	// {
	// 	ClipSocket->AttachActor(AmmoContainer, WeaponMesh);
	// }
}

void ARangeWeapon::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	if(WeaponDataRow.DataTable.Get() && WeaponDataRow.RowName.IsValid())
	{
		if(const FWeaponData* WeaponData =  WeaponDataRow.DataTable->FindRow<FWeaponData>(WeaponDataRow.RowName, TEXT("")))
		{
			bVisualizeScatter = WeaponData->bVisualizeScatter;
			bAutomatic = WeaponData->bAutomatic;
			FireInterval = WeaponData->WeaponStatistics.FireInterval;
			MarksmanFOV = WeaponData->WeaponStatistics.MarksmanFOV;
			MarksmanInterpSpeed = WeaponData->WeaponStatistics.MarksmanInterpSpeed;

			RunModifier = WeaponData->WeaponStatistics.RunModifier;
			JumpModifier = WeaponData->WeaponStatistics.JumpModifier;
			MarksmanModifier = WeaponData->WeaponStatistics.MarksmanModifier;
		}
	}
}

void ARangeWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ARangeWeapon, Ammo);
}

void ARangeWeapon::OnRep_Owner()
{
	Super::OnRep_Owner();
	if(Owner != nullptr)
	{
		SetHUDAmmo();
	}
}

void ARangeWeapon::Trigger(const FVector& HitTarget)
{
	if(IsValid(FireAnimation))
	{
		WeaponMesh->PlayAnimation(FireAnimation, false);
	}
	if(CasingClass)
	{
		if(const USkeletalMeshSocket* AmmoEjectSocket = WeaponMesh->GetSocketByName(FName("AmmoEject")))
		{
			const FTransform SocketTransform = AmmoEjectSocket->GetSocketTransform(WeaponMesh);
			if(UWorld* World = GetWorld())
			{
				World->SpawnActor<ACasing>(
					CasingClass,
					SocketTransform.GetLocation(),
					SocketTransform.GetRotation().Rotator()
				);
			}
		}
	}
	SpendRound();
}

void ARangeWeapon::SpendRound()
{
	// Ammo = FMath::Clamp(Ammo - 1, 0, MagCapacity);
	// SetHUDAmmo();

	//~ Internally Loaded
	if(AmmoContainerType == EAmmoContainerType::EACT_Internal)
	{
		GEngine->AddOnScreenDebugMessage(132, 8.f, FColor::Purple, FString::Printf(TEXT("Internal Count: %d"), Ammo));
		Ammo = FMath::Clamp(Ammo - 1, 0, MagCapacity);
		SetHUDAmmo();
	}
	
	//~ Missing Magazine
	if(!AttachmentMap.Contains(EAttachmentType::EAT_Magazine))
	{
		GEngine->AddOnScreenDebugMessage(132, 8.f, FColor::Purple, FString::Printf(TEXT("No magazine !")));
		if(EmptyContainerSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, EmptyContainerSound, GetActorLocation());
		}
		return;
	}
	
	//~ Loaded With A Magazine or Similar
	if (UAttachmentComponent* Component =  *AttachmentMap.Find(EAttachmentType::EAT_Magazine))
	{
		if (UAmmoContainer* Magazine = Cast<UAmmoContainer>(Component))
		{
			Magazine->UseAvailableRound();
			GEngine->AddOnScreenDebugMessage(132, 8.f, FColor::Purple, FString::Printf(TEXT("Ammo Left: %d"), Magazine->GetCurrentCount()));
		}
	}
}

bool ARangeWeapon::HasAmmo()
{
	if(AmmoContainerType == EAmmoContainerType::EACT_Internal)
	{
		GEngine->AddOnScreenDebugMessage(132, 8.f, FColor::Purple, FString::Printf(TEXT("Internal Count: %d"), Ammo));
		return Ammo > 0;
	}
	if(!AttachmentMap.Contains(EAttachmentType::EAT_Magazine))
	{
		GEngine->AddOnScreenDebugMessage(132, 8.f, FColor::Purple, FString::Printf(TEXT("No magazine !")));
		return false;
	}
	if (UAttachmentComponent* Component =  *AttachmentMap.Find(EAttachmentType::EAT_Magazine))
	{
		if (UAmmoContainer* Magazine = Cast<UAmmoContainer>(Component))
		{
			GEngine->AddOnScreenDebugMessage(132, 8.f, FColor::Purple, FString::Printf(TEXT("Ammo Left: %d"), Magazine->GetCurrentCount()));
			return Magazine->GetCurrentCount() > 0;
		}
	}
	return Ammo > 0;
}

void ARangeWeapon::AddRounds(const int32 RoundsToAdd)
{
	Ammo = FMath::Clamp(Ammo + RoundsToAdd, 0, MagCapacity);
	SetHUDAmmo();
}

void ARangeWeapon::OnRep_Ammo()
{
	OwnerCharacter = OwnerCharacter == nullptr ? Cast<APlayerCharacter>(GetOwner()) : OwnerCharacter;
	if(IsValid(OwnerCharacter) && OwnerCharacter->GetCombatComponent() && IsFull())
	{
		OwnerCharacter->GetCombatComponent()->JumpToReloadEnd();
	}
	SetHUDAmmo();
}

void ARangeWeapon::SetHUDAmmo()
{
	OwnerCharacter = OwnerCharacter == nullptr ? Cast<APlayerCharacter>(GetOwner()) : OwnerCharacter;
	if(OwnerCharacter)
	{
		OwnerController = OwnerController == nullptr ? Cast<ACharacterPlayerController>(OwnerCharacter->Controller) : OwnerController;
		if (OwnerController)
		{
			OwnerController->SetHUDWeaponAmmo(Ammo);
		}
	}
}