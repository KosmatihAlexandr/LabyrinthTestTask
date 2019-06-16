// Fill out your copyright notice in the Description page of Project Settings.

#include "LabyrinthPawn.h"
#include "Labyrinth.h"
#include "Kismet/GameplayStatics.h"

ALabyrinthPawn::ALabyrinthPawn()
{
	PrimaryActorTick.bCanEverTick = true;

    YawRotator = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(YawRotator);

    PitchRotator = CreateDefaultSubobject<USceneComponent>(TEXT("PitchRotator"));
    PitchRotator->SetupAttachment(RootComponent);
}

void ALabyrinthPawn::BeginPlay()
{
	Super::BeginPlay();
	
    FiandLabyrinth();
}

void ALabyrinthPawn::AddYaw(float yaw)
{
    YawRotator->AddRelativeRotation(FRotator(0.f, yaw, 0.f));
}

void ALabyrinthPawn::AddPitch(float pitch)
{
    float new_rotation = FMath::Clamp(PitchRotator->RelativeRotation.Pitch + pitch, -90.f, 0.f);
    PitchRotator->SetRelativeRotation(FRotator(new_rotation, 0.f, 0.f));
}

void ALabyrinthPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALabyrinthPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ALabyrinthPawn::FiandLabyrinth()
{
    TArray<AActor*> actors;
    UGameplayStatics::GetAllActorsOfClass(this, ALabyrinth::StaticClass(), actors);

    if (actors.Num() > 0)
    {
        Labyrinth = Cast<ALabyrinth>(actors[0]);
    }
}

bool ALabyrinthPawn::IsValidRotation(FQuat rotation) const
{
    if (!IsValid(Labyrinth))
    {
        return true;
    }

    FVector lab_up = Labyrinth->LabyrinthRoot->GetUpVector();
    FVector pawn_up = rotation.GetForwardVector() * (-1.f);

    float dot = FVector::DotProduct(lab_up, pawn_up);

    return dot > 0;
}

