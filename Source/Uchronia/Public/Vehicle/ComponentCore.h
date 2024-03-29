// Retropsis @ 2023-2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ComponentCore.generated.h"

class UVehicleCore;
class USKM_ComponentCore;
enum class EGears : uint8;
class AVehicle;

UCLASS()
class UCHRONIA_API AComponentCore : public AActor
{
	GENERATED_BODY()
	
public:	
	AComponentCore();
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable) void SetOwningVehicle(AVehicle* InVehicle);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent) void OnOwningVehicleSet();
	UFUNCTION(BlueprintCallable) void InitializeComponentCore(AVehicle* InVehicle);
	UFUNCTION() virtual void HandleOnGearChanged(EGears NewGear);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent) void ToggleEngineTrail(bool bShouldActivate);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent) void SetAnimInstance();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<AVehicle> OwningVehicle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UVehicleCore> VehicleCore;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle ComponentDataRow;

protected:
	virtual void BeginPlay() override;

public:
};
