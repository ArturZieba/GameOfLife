// Fill out your copyright notice in the Description page of Project Settings.


#include "GOL.h"
#include "Cell.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
UGOL::UGOL()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

	CalculationActive = false;
}

// Called when the game starts or when spawned
void UGOL::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickInterval(0.5f);
}

// Called every frame
void UGOL::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType , ThisTickFunction);

	if (CalculationActive)
	{
		UpdateNextGeneration(false);
		UpdateNextGeneration(true);
	}
}

void UGOL::ToggleCalculationActive()
{
	CalculationActive = !CalculationActive;
}

void UGOL::CreateGrid(int32 X, int32 Y, float CellPadding, float BaseLocationX, float BaseLocationY ) 
{
	int32 i, j;
	FVector Location;
	FRotator Rotation;
	FActorSpawnParameters SpawnParameters;
	AActor* SpawnedCell;
	ACell* SpawnedCellActor;

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.Owner = GetOwner();
	SpawnParameters.bNoFail = true;

	Rotation = FRotator::ZeroRotator;

	GridSizeX = X;
	GridSizeY = Y;

	for (i = 0; i < X; i++)
	{
		for (j = 0; j < Y; j++)
		{
			Location.X = (i * CellPadding) + BaseLocationX;
			Location.Y = (j * CellPadding) + BaseLocationY;
			Location.Z = 0;

			SpawnedCell = GetWorld()->SpawnActor(Cell, &Location, &Rotation, SpawnParameters);
			if (SpawnedCell)
			{
				SpawnedCellActor = Cast<ACell>(SpawnedCell);
				if (SpawnedCellActor)
				{
					SpawnedCellActor->SetCoordinates(i, j);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("AGOL::CreateGrid : Actor of a wrong type has been spawned"))
				}
			}

			if (!Cells.Contains(i))
			{
				TMap<int32, AActor*> NewMap;
				Cells.Add(i, NewMap);
			}

			if (!Cells[i].Contains(j))
			{
				Cells[i].Add(j, SpawnedCell);
			}
			else
			{
				Cells[i][j] = SpawnedCell;
			}
		}
	}
}

void UGOL::UpdateNextGeneration(bool SetNewState)
{
	int32 i, j;
	ACell* CellActor;

	//Cells check their state in the next generation
	for (i = 0; i < GridSizeX; i++)
	{
		for (j = 0; j < GridSizeY; j++)
		{
			CellActor = Cast<ACell>(Cells[i][j]);
			if (CellActor)
			{
				if (SetNewState)
				{
					CellActor->SetNewState();
				}
				else
				{
					CellActor->CalculateNextState(Cells);
				}
			}
		}
	}
}
