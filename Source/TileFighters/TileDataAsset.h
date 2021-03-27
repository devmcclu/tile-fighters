// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TileDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class TILEFIGHTERS_API UTileDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	public: 
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FSlateBrush TileIcon;
		
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UStaticMesh* TileMesh;
	
		FPrimaryAssetId GetPrimaryAssetId() const override
		{
		return FPrimaryAssetId("Tiles", GetFName());
		}
};
