// Fill out your copyright notice in the Description page of Project Settings.

#include "LabyrinthGeneerator.h"

bool ULabyrinthGeneerator::GenerateLabyrinth(FLabyrinthData& OutData, int32 sizeX, int32 sizeY)
{
    return false;
}

bool ULabyrinthGeneeratorEllers::GenerateLabyrinth(FLabyrinthData& OutData, int32 sizeX, int32 sizeY)
{
    if (sizeX <= 0 || sizeY <= 0)
    {
        return false;
    }
    
    TArray<uint32> group_array;
    group_array.SetNum(sizeX);

    for (uint32 i = 0; i < (uint32)sizeX; i++)
    {
        group_array[i] = i + 1;
    }

    for (uint32 i = 0; i < ((uint32)sizeY - 1); i++)
    {
        TSet<uint32> is_group_open;
        for (uint32 j = 0; j < ((uint32)sizeX - 1); j++)
        {
            if (group_array[j] == group_array[j + 1])
            {
                OutData.VerticalWalls.Add(FIntPoint(j, i));
            }
            else if (FMath::RandBool())
            {
                OutData.VerticalWalls.Add(FIntPoint(j, i));
            }
            else
            {
                uint32 tmp_group = group_array[j + 1];
                for (uint32 k = j + 1; k < (uint32)sizeX; k++)
                {
                    if (group_array[k] == tmp_group)
                    {
                        group_array[k] = group_array[j];
                    }
                }
            }

            bool is_last_of_grup = true;
            for (uint32 k = j + 1; k < (uint32)sizeX; k++)
            {
                if (group_array[k] == group_array[j])
                {
                    is_last_of_grup = false;
                    break;
                }
            }

            if (FMath::RandBool() && (!is_last_of_grup || is_group_open.Contains(group_array[j])))
            {
                OutData.HorisontalWalls.Add(FIntPoint(j, i));
                group_array[j] = sizeX * (i + 1) + j + 1;
            }
            else
            {
                is_group_open.Add(group_array[j]);
            }
        }

        if (FMath::RandBool() && is_group_open.Contains(group_array[sizeX - 1]))
        {
            OutData.HorisontalWalls.Add(FIntPoint(sizeX - 1, i));
            group_array[sizeX - 1] = 0;
        }

        is_group_open.Empty();
    }

    for (uint32 i = 0; i < ((uint32)sizeX - 1); i++)
    {
        if (group_array[i] == group_array[i + 1])
        {
            OutData.VerticalWalls.Add(FIntPoint(i, sizeY - 1));
        }
    }

    return true;
}