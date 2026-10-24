#include "PonyEngine/Application/Module.h"
#include "Game/GameModule.h"

PONY_PROJECT_MODULE(Game::GetProviderModule, ProviderModule, ta)
PONY_PROJECT_MODULE(Game::GetConsumerModule, ConsumerModule, tb)
