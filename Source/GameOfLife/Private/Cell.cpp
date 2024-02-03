// Fill out your copyright notice in the Description page of Project Settings.


#include "Cell.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ACell::ACell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Add a Root Scene and Static Mesh components to the Cell
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshComponentCellAlive(TEXT("/Script/Engine.StaticMesh'/Game/StaticMeshes/SM_CellAlive.SM_CellAlive'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshComponentCellDead(TEXT("/Script/Engine.StaticMesh'/Game/StaticMeshes/SM_CellDead.SM_CellDead'"));

	if (MeshComponentCellAlive.Object)
	{
		CellAliveMesh = MeshComponentCellAlive.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ACell::ACell() : Failed to find Static Mesh for alive cell"))
	}
	if (MeshComponentCellDead.Object)
	{
		CellDeadMesh = MeshComponentCellDead.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ACell::ACell() : Failed to find Static Mesh for dead cell"))
	}
	

	SetCellDead();

	//Attach Static Mesh component to the Root Scene Component
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void ACell::SetCellAlive()
{
	StaticMeshComponent->SetStaticMesh(CellAliveMesh);
}

void ACell::SetCellDead()
{
	StaticMeshComponent->SetStaticMesh(CellDeadMesh);
}

// Called when the game starts or when spawned
void ACell::BeginPlay()
{
	Super::BeginPlay();

	UKismetSystemLibrary::PrintString(this, FString("Cell"));
}

// Called every frame
void ACell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

