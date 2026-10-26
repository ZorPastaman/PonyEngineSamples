# Buffer sample

Shows how to use application buffers.

The application module keeps a pool of buffers. On your request the application tries to find a suitable buffer in the pool.
If it's found, it's simply returned. Otherwise the application will return a new buffer. It greatly reduces heap allocations.
When the returned buffer goes of out scope, it's returned to the pool.

## Details

The sample of module usage is entirely in the `Tick()` function of the [GameTicker](Source/Game-GameTicker.cppm).

First, it calculates a required buffer size via `PonyEngine::Memory::CalculateBufferSize()`. 
If it's not a first array in a request buffer, set the second template argument to a type of a previous array.
It will allow to calculate a valid padding to keep a correct alignment.

Second, call `CreateBuffer()` on the `PonyEngine::Application::IApplication` instance.
The buffer itself is just a span. To make it easier to use, use `PonyEngine::Memory::Arena`.
It will help with allocations inside the buffer.

Third, allocate arrays via the arena. It's important to use the same counts as they were requested.
And now you can use those array as you want.

When the function returns, the buffer will be automatically returned to the pool.
The buffer isn't cleared on return to the pool. If it's a problem for your usage, clear it manually.
