// Fill out your copyright notice in the Description page of Project Settings.

#include "LabyrinthGeneerator.h"

FLabyrinthData ULabyrinthGeneerator::GenerateLabyrinth(int32 sizeX, int32 sizeY)
{
    return FLabyrinthData();
}

FLabyrinthData ULabyrinthGeneeratorEllers::GenerateLabyrinth(int32 sizeX, int32 sizeY)
{
    FLabyrinthData data = FLabyrinthData();
    for (int i = 0; i < 20; i++)
    {
        data.VerticalWalls.Add(FIntPoint(FMath::RandRange(0, sizeX - 2), FMath::RandRange(0, sizeY - 1)));
    }
    for (int i = 0; i < 20; i++)
    {
        data.HorisontalWalls.Add(FIntPoint(FMath::RandRange(0, sizeX - 1), FMath::RandRange(0, sizeY - 2)));
    }
    return data;
}