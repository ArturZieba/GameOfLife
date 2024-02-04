// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cell.generated.h"

UCLASS()
class GAMEOFLIFE_API ACell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACell();
	UFUNCTION()
	void Clicked();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetCoordinates(int32 CellX, int32 CellY);
	
	void IsCellAlive(bool& Alive);
	
	void CalculateNextState(TMap<int32, TMap<int32, AActor*>> CellGrid);

	void SetNewState();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UStaticMesh* CellAliveMesh;
	UStaticMesh* CellDeadMesh;
	bool IsAlive;
	bool NextState;
	int32 X;
	int32 Y;

	void SetCellAlive();
	void SetCellDead();
};
