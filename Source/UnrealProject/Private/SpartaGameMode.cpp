#include "SpartaGameMode.h"
#include "SpartaCharacter.h"
#include "PawnCharacter.h"
#include "SpartaPlayerController.h"
#include "SpartaGameState.h"


ASpartaGameMode::ASpartaGameMode()
{
	DefaultPawnClass = APawnCharacter::StaticClass();
	PlayerControllerClass = ASpartaPlayerController::StaticClass();
	GameStateClass = ASpartaGameState::StaticClass();
}