# Resource main sample

Shows how to make a world definition resource and load it as a world at runtime.

World definition resources are used to create worlds out of them.

For more details about worlds and world definitions including their resource, refer to the engine documentation.

## Details

The whole sample is described in [Game](Source/Game.cppm) and [CMakeLists](CMakeLists.txt).

The world asset is [World](Assets/World.toml). It contains some entities with transforms, names and descriptions.

The world definition asset is built via `pony_compiler_world_definition`.
At runtime it's loaded as usual, then a world is created out of it via a function in `PonyEngine::World::IWorldService`.
