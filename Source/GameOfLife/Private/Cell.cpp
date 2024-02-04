// Fill out your copyright notice in the Description page of Project Settings.


#include "Cell.h"
#include "Kismet/KismetMathLibrary.h"

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

	//Randomize state on initial spawn
	if (UKismetMathLibrary::RandomBool()) 
	{
		SetCellAlive();
	}
	else
	{
		SetCellDead();
	}

	//Attach Static Mesh component to the Root Scene Component
	StaticMeshComponent->SetupAttachment(RootComponent);

	//On clicked implementation
	FScriptDelegate Delegate;
	Delegate.BindUFunction(this, "Clicked");
	OnClicked.Add(Delegate);
}

void ACell::Clicked()
{
	if (IsAlive)
	{
		SetCellDead();
	}
	else
	{
		SetCellAlive();
	}
}

void ACell::SetCellAlive()
{
	IsAlive = true;
	StaticMeshComponent->SetStaticMesh(CellAliveMesh);
}

void ACell::SetCellDead()
{
	IsAlive = false;
	StaticMeshComponent->SetStaticMesh(CellDeadMesh);
}

// Called when the game starts or when spawned
void ACell::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACell::SetCoordinates(int32 CellX, int32 CellY)
{
	X = CellX;
	Y = CellY;
}

void ACell::IsCellAlive(bool& Alive)
{
	Alive = IsAlive;
}

void ACell::CalculateNextState(TMap<int32, TMap<int32, AActor*>> CellGrid)
{
	int32 AliveNeighbours;
	int32 i;
	int32 j;
	ACell* Cell;
	bool NeighbourIsAlive;

	//Itarate over all neighbouring cells and check if they are alive
	AliveNeighbours = 0;
	for (i = -1; i <= 1; i++)
	{
		for (j = -1; j <= 1; j++)
		{
			//Skip the cell checking neighbours (0,0 coordinate)
			if (!((i == 0) && (j == 0)))
			{
				//Check that there is a cell at the grid coordinate or if it is cast outside the grid
				if (CellGrid.Contains(X + i))
				{
					if (CellGrid[X + i].Contains(Y + j))
					{
						Cell = Cast <ACell>(CellGrid[X + i][Y + j]);
						if (Cell)
						{
							Cell->IsCellAlive(NeighbourIsAlive);
							if (NeighbourIsAlive)
							{
								AliveNeighbours++;
							}
						}
					}
				}
			}
		}
	}

	//Apply Game of Life rules
	if (IsAlive && (AliveNeighbours < 2))
	{
		NextState = false;
	}
	else if (IsAlive && (AliveNeighbours == 2 || (AliveNeighbours == 3)))
	{
		NextState = true;
	}
	else if (IsAlive && (AliveNeighbours > 3))
	{
		NextState = false;
	}
	else if (!IsAlive && (AliveNeighbours == 3))
	{
		NextState = true;
	}
}

void ACell::SetNewState()
{
	IsAlive = NextState;
	if (IsAlive)
	{
		SetCellAlive();
	}
	else
	{
		SetCellDead();
	}
}