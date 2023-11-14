// Fill out your copyright notice in the Description page of Project Settings.


#include "FaceOpponent.h"

// Sets default values for this component's properties
UFaceOpponent::UFaceOpponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFaceOpponent::BeginPlay()
{
	Super::BeginPlay();

	LookRight = this->GetOwner()->GetActorScale();
	LookLeft = this->GetOwner()->GetActorScale();
	LookLeft.Y = -1;
}


// Called every frame
void UFaceOpponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (this->GetOwner()->GetTargetLocation().Y < -10 && bMirrored == false)
	{
		this->GetOwner()->SetActorScale3D(LookLeft);
		bMirrored = true;
	} else
	if (this->GetOwner()->GetTargetLocation().Y > -10 && bMirrored == true)
	{
		this->GetOwner()->SetActorScale3D(LookRight);
		bMirrored = false;
	}
}