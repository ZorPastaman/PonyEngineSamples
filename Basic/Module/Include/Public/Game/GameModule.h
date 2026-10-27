#pragma once

#include "PonyEngine/Application/Module.h"

import std;

import PonyEngine.Application;

namespace Game
{
	// Module function declaration.
	[[nodiscard("Pure function")]]
	PONY_MODULE_FUNC std::shared_ptr<PonyEngine::Application::IModule> GetGameModule();
}
