# Module sample

Shows how to build a custom engine module.

## Steps

1. Add an application module class. Example: [Game.cppm](Source/Game.cppm)
2. Add launch files. Example: [Launch.cpp](Source/Launch.cpp), [Launch.Impl.cpp](Source/Launch.Impl.cpp), [GameModule.h](Include/Public/Game/GameModule.h)
3. Assemble everything in [CMakeLists](CMakeLists.txt)

## Details

An application module must inherit `PonyEngine::Application::IModule` and implement it.

The launch files have that strange layout because of this. The Game module is private but exported functions must lie in the public section.
CMake doesn't allow to mix them. That's why it has private `Launch.Impl` that imports the Game module and implements a function from the header `GameModule.h`
while public `Launch` declares the application module and points to the function from the header `GameModule.h`. Public and private files may interact via headers.

The module main function must have this signature `PONY_MODULE_FUNC std::shared_ptr<PonyEngine::Application::IModule> FunctionName();`.

The module declaration looks like this: `PONY_PROJECT_MODULE(Game::GetGameModule, GameModule, ga)`.
It uses `PONY_PROJECT_MODULE` because it guarantees that the game module will be started up after all the engine modules.
The first argument is a pointer to a module main function. The second argument may be any unique string.
The last argument controls a start-up order among project modules. In this example it doesn't matter because it has only one module.
