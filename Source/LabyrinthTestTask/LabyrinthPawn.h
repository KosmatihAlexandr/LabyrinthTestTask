// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LabyrinthPawn.generated.h"

class ALabyrinth;

UCLASS()
class LABYRINTHTESTTASK_API ALabyrinthPawn : public APawn
{
	GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* YawRotator;

    UPROPERTY(VisibleAnywhere)
    USceneComponent* PitchRotator;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Labyrinth")
    ALabyrinth* Labyrinth;

public:
	ALabyrinthPawn();

protected:
	virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Moving")
    void AddYaw(float yaw);

    UFUNCTION(BlueprintCallable, Category = "Moving")
    void AddPitch(float pitch);
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    void FiandLabyrinth();

    bool IsValidRotation(FQuat rotation) const;
};
