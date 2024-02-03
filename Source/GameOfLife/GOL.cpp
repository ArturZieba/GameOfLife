// Fill out your copyright notice in the Description page of Project Settings.


#include "GOL.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AGOL::AGOL()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AGOL::BeginPlay()
{
	Super::BeginPlay();

	/*
	//Initialize both grids with chosen X and Y dimensions
	Original.Init(FMath::RandRange(0, 1), DisplayX);
	Swap.Init(FMath::RandRange(0, 1), DisplayX);
	
	OriginalMap.Add(Original, DisplayY);
	SwapMap.Add(Swap, DisplayY);

	
	for (int i = 0; i < Original.Num(); i++)
	{
		Original.Insert(FMath::RandRange(0, 1), i);
		//UE_LOG(LogClass, Log, TEXT("%d"), Original[row]);
	}
	*/

	//Spawn Cell chosen cell actor
	//GetWorld()->SpawnActor<AActor>(Cell, GetActorLocation(), GetActorRotation());

	CreateGrid(DisplayX, DisplayY, true);
}

// Called every frame
void AGOL::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGOL::CreateGrid(int X, int Y, bool Alive) 
{
	int i, j;

	for (i = 0; i < X; i++) 
	{
		for (j = 0; j < Y; j++)
		{
			GetWorld()->SpawnActor<AActor>(Cell, GetActorLocation() + GetActorLocation().X * i + GetActorLocation().Y * j, GetActorRotation());
			UE_LOG(LogClass, Log, TEXT("%d , %d"), i, j);
		}
	}
}