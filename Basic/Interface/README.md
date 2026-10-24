# Interface sample

Shows how to add a custom interface to the engine application, find it and use it.

## Steps for an interface provider

1. Make a custom interface class. Example: [IInterface](Source/Game-IInterface.cppm)
2. Make a class that implements the interface. Example: [InterfaceProvider](Source/Game-InterfaceProvider.cppm)
3. Make a provider module. Example: [InterfaceProviderModule](Source/Game-InterfaceProviderModule.cppm)
4. Create a provider and add its interface to the engine application on start-up.
5. Remove the interface from the engine application on shut-down and destroy its provider.

## Steps for an interface consumer

1. Make a class that consumes the interface. Example: [InterfaceConsumer](Source/Game-InterfaceConsumer.cppm)
2. Make a consumer module. Example: [InterfaceConsumerModule](Source/Game-InterfaceConsumerModule.cppm)
3. Create a consumer on start-up.
4. Get or find interfaces.
5. Destroy the consumer on shut-down.

## Details

The engine application keeps a list of interfaces. They can be any class but one interface type may be added only once.
The interfaces may be added only on start-up and removed on shut-down via `PonyEngine::Application::IModuleContext`.

The interfaces can be found via `PonyEngine::Application::IApplication`. It has two function for that: `FindInterface()` and `GetInterface()`.
`FindInterface()` returns a pointer to the interface if it's found or nullptr otherwise.
`GetInterface()` returns a reference to the interface if it's found or throws an exceptions otherwise.
The example of the consumer class also tries to find an interface that no class implements to demonstate both functions.

It's important that consumer module starts up after the provider module. Otherwise, it won't find the interfaces.
See [Launch](Source/Launch.cpp).
