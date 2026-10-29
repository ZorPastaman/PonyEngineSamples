# Flow sample

Shows how to use main flow functions of the engine application.

The main functions are:

1. `DeltaTimeSeconds()` - returns a delta time in seconds since the last frame.
2. `FrameCount()` - returns how many frames has passed since the start of the application.
3. `Stop()` - stops the application. In the end of a frame the process will be closed.
4. `TargetFrameTimeSeconds()` - gets or sets a target frame time in seconds.

## Details

The sample class is [GameTicker](Source/Game-GameTicker.cppm).

The workflow of the application is based on frames. Every frame the application ticks registered tickables.
The application updates delta time and other time and frame related info as well. Refer to `PonyEngine::Application::IApplication` docs for more info.

The frequency of ticks may be restricted or unrestricted with `TargetFrameTimeSeconds()`.
Pay attention that this function is based on a period, not on a frequency.

The application may be stopped with `Stop()` function call. In this case, the application will finish a current frame and closes its process.
