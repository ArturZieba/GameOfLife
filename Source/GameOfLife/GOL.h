// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "GOL.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAMEOFLIFE_API UGOL : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UGOL();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Cell;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void ToggleCalculationActive();
	UFUNCTION(BlueprintCallable)
	void CreateGrid(int32 X, int32 Y, float CellPadding, float BaseLocationX, float BaseLocationY);

	void UpdateNextGeneration(bool SetNewState);

private:
	TMap<int32, TMap<int32, AActor*>> Cells;
	int32 GridSizeX;
	int32 GridSizeY;
	bool CalculationActive;
};
