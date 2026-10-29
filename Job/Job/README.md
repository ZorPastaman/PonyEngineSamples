# Job sample

Shows the main API of the job module.

## Details 

The sample class is [GameTicker](Source/Game-GameTicker.cppm).

The main interface is `PonyEngine::Job::IJobService`. It may be gotten from the application.

Its API is quite simple. It has a `Schedule` function which takes a task (`std::move_only_function<void() noexcept>`)
and optionally `PonyEngine::Job::JobParams`. It returns `PonyEngine::Job::JobHandle` 
which allows to make the job a dependency or wait for it to finish.
The job service will execute the task on one of worker threads.
`PonyEngine::Job::JobParams` contains dependencies. The task won't be executed till all its dependencies are finished.
