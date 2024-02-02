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

	UKismetSystemLibrary::PrintString(this, FString("GOL"));
}

// Called every frame
void AGOL::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

