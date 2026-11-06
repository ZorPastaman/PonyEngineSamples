# World query sample

Shows how to use component queries.

Though you can use simple `GetComponents()` functions, it's not a good idea when you need a complex search for entities.
That's where the queries come. They allow to make a special request that tells what components should the entities have.

There are 3 types of a component type in a query:

- Required - an entity must have a component of this type.
- Excluded - an entity mustn't have a component of this type.
- Optional - an entity may have a component of this type, it doesn't affect a query. 
But if the entity has such a compoent, it's returned; otherwise it's nullptr.

## Details

The whole sample is in [Game](Source/Game.cppm).

To use queries you need to follow these steps.

1. Make a query struct. Call `PonyEngine::World::MakeQuery()` and pass `PonyEngine::World::Required<Args...>`, 
`PonyEngine::World::Excluded<Args...>` and `PonyEngine::World::Optional<Args...>`.
You can use any combination of them. The only rule that types inside must be registered components and must be
used only once among all the three arguments in one query.
2. Call `PonyEngine::World::IWorld::Query()` to make a request.
You pass a `QueryParams` from the query struct created in the precious step
and a callback function `std::function<void(PonyEngine::World::QueryItem&)>`.
3. When the query finds an entity that fully satisfies the request, it will call the callback.
The `PonyEngine::World::QueryItem` contains pointers to the required components (can't be nullptr),
optional components (can be nullptr) and an entity.
To access the components easier, use `GetRequired<T>()` and `GetOptional<T>()` functions 
on the query struct passing the item into them.
4. The `QueryItem` has a `terminate` flag as well. By default, it's `false`.
If you set it to `true`, the query will terminate even if there are other entities that satisfy the request.
