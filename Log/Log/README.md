# Log sample

Main log sample. Shows how to log.

## Details

The whole sample is in [Game](Source/Game.cppm).

It shows 3 ways to log:

1. Via `PonyEngine::Log::ILogService` interface directly.
2. Via `PonyEngine::Log::LogToLogService()` helper functions.
3. Via `PONY_LOG` macro.

`PONY_LOG` macro is a preferable way. It respects log type and stacktrace defines.
The other two ways are used only when you really have to use them.
