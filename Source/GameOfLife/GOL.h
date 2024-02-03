// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GOL.generated.h"

UCLASS()
class GAMEOFLIFE_API AGOL : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGOL();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> Cell;
	UPROPERTY(EditDefaultsOnly)
	int DisplayX = 10;
	UPROPERTY(EditDefaultsOnly)
	int DisplayY = 10;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void CreateGrid(int, int, bool);
};
