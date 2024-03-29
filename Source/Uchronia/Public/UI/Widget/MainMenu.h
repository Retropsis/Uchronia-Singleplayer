// Retropsis @ 2023-2024

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/BaseUserWidget.h"
#include "MainMenu.generated.h"

class UGridInventory;
class UInventoryComponent;
class APlayerCharacter;
/**
 * 
 */
UCLASS()
class UCHRONIA_API UMainMenu : public UBaseUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<APlayerCharacter> PlayerCharacter;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UGridInventory> GridInventory;

	UPROPERTY(EditAnywhere)
	float TileSize;

	UPROPERTY()
	TObjectPtr<UInventoryComponent> InventoryComponent;
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation) override;

};
