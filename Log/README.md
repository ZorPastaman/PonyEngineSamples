# Log samples

Shows how to use the log module.

The log module provides an interface for logging. Its central interface `PonyEngine::Log::ILogService` 
doesn't log anything itself. It formats a log string and sends it to registered loggers.

Standard log formatting:
`<LogTypeFirstLetter> | <ThreadID> : [<Time>] <Message>`

## Samples

| Sample         | Description      |
|:---------------|:-----------------|
| [Log](Log)     | Main log sample. |
