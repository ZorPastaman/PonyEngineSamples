#include "Game/GameModule.h"

import Game;

namespace Game
{
	std::shared_ptr<PonyEngine::Application::IModule> GetGameModule()
	{
		return std::make_shared<GameModule>(); // Module function usually just creates a module and returns it.
	}
}
