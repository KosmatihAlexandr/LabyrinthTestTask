 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Labyrinth.generated.h"

class ULabyrinthGeneerator;
struct FLabyrinthData;

UCLASS()
class LABYRINTHTESTTASK_API ALabyrinth : public AActor
{
	GENERATED_BODY()
	
public:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Root;

    UPROPERTY(VisibleAnywhere)
    USceneComponent* PitchRotator;

    UPROPERTY(VisibleAnywhere)
    USceneComponent* YawRotator;

    UPROPERTY(VisibleAnywhere)
    USceneComponent* LabyrinthRoot;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Labyrinth settings")
    TSubclassOf<ULabyrinthGeneerator> LabyrinthGeneratorClass;

    UPROPERTY(EditDefaultsOnly, Category = "Labyrinth settings")
    UStaticMesh* WallMesh;

    UPROPERTY(EditDefaultsOnly, Category = "Labyrinth settings")
    UStaticMesh* FloorMesh;

    UPROPERTY(EditDefaultsOnly, Category = "Labyrinth settings")
    int32 Size;

    UPROPERTY(EditDefaultsOnly, Category = "Labyrinth settings")
    float WallSize;

private:
    ULabyrinthGeneerator* LabyrinthGenerator;

    TArray<USceneComponent*> Walls;

public:	
	ALabyrinth();

    UFUNCTION(BlueprintCallable, Category = "Labyrinth")
    void GenerateLabyrinth();

protected:
	virtual void BeginPlay() override;

private:
    void MakeSideWaalsAndFloor();

    void BuildWalls(FLabyrinthData& data);
    void DeleteWalls();
};
