// Fill out your copyright notice in the Description page of Project Settings.

#include "Labyrinth.h"
#include "LabyrinthGeneerator.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

ALabyrinth::ALabyrinth()
{
	PrimaryActorTick.bCanEverTick = true;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(Root);

    PitchRotator = CreateDefaultSubobject<USceneComponent>(TEXT("PitchRotator"));
    PitchRotator->SetupAttachment(Root);

    YawRotator = CreateDefaultSubobject<USceneComponent>(TEXT("YawRotator"));
    YawRotator->SetupAttachment(PitchRotator);

    LabyrinthRoot = CreateDefaultSubobject<USceneComponent>(TEXT("LabyrinthRoot"));
    LabyrinthRoot->SetupAttachment(YawRotator);
    
}

void ALabyrinth::GenerateLabyrinth()
{
    if (!IsValid(LabyrinthGenerator))
    {
        UE_LOG(LogTemp, Error, TEXT("Have not labyrinth generator."));
        return;
    }

    FLabyrinthData data = LabyrinthGenerator->GenerateLabyrinth(Size, Size);

    BuildWalls(data);
}

void ALabyrinth::BeginPlay()
{
	Super::BeginPlay();
	
    LabyrinthGenerator = NewObject<ULabyrinthGeneerator>(this, LabyrinthGeneratorClass);

    MakeSideWaalsAndFloor();

    GenerateLabyrinth();
}

void ALabyrinth::MakeSideWaalsAndFloor()
{
    if (Size <= 0 || !FloorMesh || !WallMesh)
    {
        return;
    }

    const float offset = -WallSize * Size / 2.f;
    LabyrinthRoot->SetRelativeLocation(FVector(offset, offset, 0.f));

    const float wall_extend = WallMesh->GetBoundingBox().GetSize().X;
    const float loc_size = WallSize * Size + wall_extend;
    const float half_extend = wall_extend / 2.f;

    UStaticMeshComponent* mesh_comp;
    FBox box;

    mesh_comp = NewObject<UStaticMeshComponent>(this, NAME_None);
    mesh_comp->RegisterComponent();
    mesh_comp->AttachToComponent(LabyrinthRoot, FAttachmentTransformRules::KeepRelativeTransform);
    mesh_comp->SetStaticMesh(FloorMesh);
    box = FloorMesh->GetBoundingBox();
    mesh_comp->SetRelativeScale3D(FVector(loc_size / box.GetSize().X, loc_size / box.GetSize().Y, 1.f));
    mesh_comp->SetRelativeLocation(FVector(-box.Min.X * mesh_comp->RelativeScale3D.X - half_extend,
        -box.Min.Y * mesh_comp->RelativeScale3D.Y - half_extend, -box.Max.Z));

    mesh_comp = NewObject<UStaticMeshComponent>(this, NAME_None);
    mesh_comp->RegisterComponent();
    mesh_comp->AttachToComponent(LabyrinthRoot, FAttachmentTransformRules::KeepRelativeTransform);
    mesh_comp->SetStaticMesh(WallMesh);
    box = WallMesh->GetBoundingBox();
    mesh_comp->SetRelativeScale3D(FVector(1.f, loc_size / box.GetSize().Y, 1.f));
    mesh_comp->SetRelativeLocation(FVector(0.f, -box.Min.Y * mesh_comp->RelativeScale3D.Y - half_extend, -box.Min.Z));

    mesh_comp = NewObject<UStaticMeshComponent>(this, NAME_None);
    mesh_comp->RegisterComponent();
    mesh_comp->AttachToComponent(LabyrinthRoot, FAttachmentTransformRules::KeepRelativeTransform);
    mesh_comp->SetStaticMesh(WallMesh);
    box = WallMesh->GetBoundingBox();
    mesh_comp->SetRelativeScale3D(FVector(1.f, loc_size / box.GetSize().Y, 1.f));
    mesh_comp->SetRelativeLocation(FVector(loc_size - wall_extend, -box.Min.Y * mesh_comp->RelativeScale3D.Y - half_extend, -box.Min.Z));

    const float loc_small_first = (Size % 2)?((loc_size - WallSize) / 2.f):(loc_size / 2.f - WallSize);
    const float loc_small_second = (Size % 2) ? ((loc_size - WallSize) / 2.f) : (loc_size / 2.f);

    mesh_comp = NewObject<UStaticMeshComponent>(this, NAME_None);
    mesh_comp->RegisterComponent();
    mesh_comp->AttachToComponent(LabyrinthRoot, FAttachmentTransformRules::KeepRelativeTransform);
    mesh_comp->SetStaticMesh(WallMesh);
    box = WallMesh->GetBoundingBox();
    mesh_comp->SetRelativeScale3D(FVector(1.f, loc_small_first / box.GetSize().Y, 1.f));
    mesh_comp->SetRelativeLocation(FVector(-box.Min.Y * mesh_comp->RelativeScale3D.Y - half_extend, 0.f, -box.Min.Z));
    mesh_comp->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

    mesh_comp = NewObject<UStaticMeshComponent>(this, NAME_None);
    mesh_comp->RegisterComponent();
    mesh_comp->AttachToComponent(LabyrinthRoot, FAttachmentTransformRules::KeepRelativeTransform);
    mesh_comp->SetStaticMesh(WallMesh);
    box = WallMesh->GetBoundingBox();
    mesh_comp->SetRelativeScale3D(FVector(1.f, loc_small_second / box.GetSize().Y, 1.f));
    mesh_comp->SetRelativeLocation(FVector(loc_size - box.Max.Y * mesh_comp->RelativeScale3D.Y - half_extend, 0.f, -box.Min.Z));
    mesh_comp->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

    mesh_comp = NewObject<UStaticMeshComponent>(this, NAME_None);
    mesh_comp->RegisterComponent();
    mesh_comp->AttachToComponent(LabyrinthRoot, FAttachmentTransformRules::KeepRelativeTransform);
    mesh_comp->SetStaticMesh(WallMesh);
    box = WallMesh->GetBoundingBox();
    mesh_comp->SetRelativeScale3D(FVector(1.f, loc_small_second / box.GetSize().Y, 1.f));
    mesh_comp->SetRelativeLocation(FVector(-box.Min.Y * mesh_comp->RelativeScale3D.Y - half_extend, loc_size - wall_extend, -box.Min.Z));
    mesh_comp->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

    mesh_comp = NewObject<UStaticMeshComponent>(this, NAME_None);
    mesh_comp->RegisterComponent();
    mesh_comp->AttachToComponent(LabyrinthRoot, FAttachmentTransformRules::KeepRelativeTransform);
    mesh_comp->SetStaticMesh(WallMesh);
    box = WallMesh->GetBoundingBox();
    mesh_comp->SetRelativeScale3D(FVector(1.f, loc_small_first / box.GetSize().Y, 1.f));
    mesh_comp->SetRelativeLocation(FVector(loc_size - box.Max.Y * mesh_comp->RelativeScale3D.Y - half_extend, loc_size - wall_extend, -box.Min.Z));
    mesh_comp->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
}

void ALabyrinth::BuildWalls(FLabyrinthData & data)
{
    for (auto point : data.VerticalWalls)
    {
        UStaticMeshComponent* mesh_comp = NewObject<UStaticMeshComponent>(this, NAME_None);
        mesh_comp->RegisterComponent();
        mesh_comp->AttachToComponent(LabyrinthRoot, FAttachmentTransformRules::KeepRelativeTransform);
        mesh_comp->SetStaticMesh(WallMesh);
        FBox box = WallMesh->GetBoundingBox();
        mesh_comp->SetRelativeLocation(FVector(WallSize * (point.X + 1), WallSize * (point.Y + 0.5f), -box.Min.Z));
    }

    for (auto point : data.HorisontalWalls)
    {
        UStaticMeshComponent* mesh_comp = NewObject<UStaticMeshComponent>(this, NAME_None);
        mesh_comp->RegisterComponent();
        mesh_comp->AttachToComponent(LabyrinthRoot, FAttachmentTransformRules::KeepRelativeTransform);
        mesh_comp->SetStaticMesh(WallMesh);
        FBox box = WallMesh->GetBoundingBox();
        mesh_comp->SetRelativeLocation(FVector(WallSize * (point.X + 0.5f), WallSize * (point.Y + 1), -box.Min.Z));
        mesh_comp->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
    }
}

void ALabyrinth::DeleteWalls()
{
    for (auto wall : Walls)
    {
        wall->DestroyComponent();
    }
}

