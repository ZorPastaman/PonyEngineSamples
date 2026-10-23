# Module sample

Shows how to add a custom tickable to the engine application.

## Steps

1. Make a custom tickable class. Example: [GameTicker](Source/Game-GameTicker.cppm)
2. Make a custom module. See [ModuleSample](../Module) for details. Example: [GameModule](Source/Game-GameModule.cppm)
3. Create the tickable on the module start-up and add it to the application tickables.
4. Remove the tickable from the application tickables and destroy it on the module shut-down.

## Details

A tickable must inherit `PonyEngine::Application::ITickable` and implement it.
It's recommended to use private inheritance so that it's impossible to get a pointer to it via `dynamic_cast` from a public interface.
In this sample though it's not demonstrated cause the tickable doesn't have any public interface.

The engine application will call `Begin()` before a first tick and `End()` after a last tick. It will call `Tick()` every tick.

The order of begin and tick executions among all added tickables is controlled via `PonyEngine::Application::TickableOrder` that's passed on adding a tickable.
The order of end is always the opposite to the oder of begin. If the corresponding order is `std::nullopt`, its function won't be called.

A module may add and remove tickables only during start-up and shut-down phases via `PonyEngine::Application::IModuleContext` 
that's passed to the corresponding module interface functions.
