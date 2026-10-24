#pragma once

#include "PonyEngine/Application/Module.h"

import std;

import PonyEngine.Application;

namespace Game
{
	[[nodiscard("Pure function")]]
	PONY_MODULE_FUNC std::shared_ptr<PonyEngine::Application::IModule> GetProviderModule();
	[[nodiscard("Pure function")]]
	PONY_MODULE_FUNC std::shared_ptr<PonyEngine::Application::IModule> GetConsumerModule();
}
