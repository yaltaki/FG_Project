// Copyright Epic Games, Inc. All Rights Reserved.

#include "FG_ProjectGameMode.h"
#include "FG_ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFG_ProjectGameMode::AFG_ProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
