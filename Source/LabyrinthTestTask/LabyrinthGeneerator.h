// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LabyrinthGeneerator.generated.h"

USTRUCT()
struct FLabyrinthData
{
    GENERATED_BODY()

    UPROPERTY()
    TArray<FIntPoint> VerticalWalls;
    UPROPERTY()
    TArray<FIntPoint> HorisontalWalls;
};

UCLASS()
class LABYRINTHTESTTASK_API ULabyrinthGeneerator : public UObject
{
	GENERATED_BODY()
	
public:
    virtual bool GenerateLabyrinth(FLabyrinthData& OutData, int32 sizeX, int32 sizeY);
};

/**
* –еализаци€ алгоритма Ёллера, создающего лабиринты, имеющие только один путь между двум€ точками и не имеющего изолированых участков
*/
UCLASS(BlueprintType)
class LABYRINTHTESTTASK_API ULabyrinthGeneeratorEllers : public ULabyrinthGeneerator
{
    GENERATED_BODY()

public:
    virtual bool GenerateLabyrinth(FLabyrinthData& OutData, int32 sizeX, int32 sizeY) override;
};
