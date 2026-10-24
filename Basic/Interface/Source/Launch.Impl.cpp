#include "Game/GameModule.h"

import Game;

namespace Game
{
	std::shared_ptr<PonyEngine::Application::IModule> GetProviderModule()
	{
		return std::make_shared<InterfaceProviderModule>();
	}

	std::shared_ptr<PonyEngine::Application::IModule> GetConsumerModule()
	{
		return std::make_shared<InterfaceConsumerModule>();
	}
}
