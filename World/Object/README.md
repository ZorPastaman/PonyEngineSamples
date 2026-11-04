# World object sample

Shows how to make an object for the world module and use it.

## Details

The whole sample is in [Game](Source/Game.cppm).

First, it registers components. It's required to add them to entities.
Second, it registers object handle members. It's required to make the garbage collection work correctly.

The world keeps objects as a key-value map of `PonyEngine::World::ObjectHandle<T>` to `PonyEngine::World::Object`.
`PonyEngine::World::Object` is a type-erased wrapper over `std::shared_ptr<T>`.

In the sample objects are created, added to the components on entities. Then it gets them from the world.

It destroys the first entity - so, it destroys a single object reference. But it still can get the object.
It happens because the objects are not removed automatically. You have to call `CollectGarbage()`.
After it, all unreferenced objects are removed from the world.
