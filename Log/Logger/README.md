# Logger sample

Shows how to make a custom logger.

## Details

The custom logger is in class [GameLogger](Source/Game-GameLogger.cppm).
It implements the interface `PonyEngine::Log::ILogger`. 
It its log function it simply writes a custom message to the console.

The game module [GameModule](Source/Game-GameModule.cppm) creates a custom logger and registers it.
To add a custom logger, get the interface `PonyEngine::Log::ILogHub` and add the logger to it.
On shut-down, you must remove the logger from the log hub.
