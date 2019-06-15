// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LabyrinthGeneerator.generated.h"

USTRUCT()
struct FLabyrinthData
{
    GENERATED_BODY()

    TArray<FIntPoint> VerticalWalls;
    TArray<FIntPoint> HorisontalWalls;
};

/**
 * 
 */
UCLASS()
class LABYRINTHTESTTASK_API ULabyrinthGeneerator : public UObject
{
	GENERATED_BODY()
	
public:
    virtual FLabyrinthData GenerateLabyrinth(int32 sizeX, int32 sizeY);
};

UCLASS(BlueprintType)
class LABYRINTHTESTTASK_API ULabyrinthGeneeratorEllers : public ULabyrinthGeneerator
{
    GENERATED_BODY()

public:
    virtual FLabyrinthData GenerateLabyrinth(int32 sizeX, int32 sizeY) override;
};
