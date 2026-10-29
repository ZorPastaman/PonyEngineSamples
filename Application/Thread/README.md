# Thread sample

Shows how to create thread with different priorities.

Different platforms have different ways to set thread priorities. To make a universal API for that, Pony Engine uses this logic.
When you create a thread, you set its role (string). This role is mapped to a platform specific priority.
That mapping is set via an application implementation module. Refer to the engine docs for more info.

## Details

The sample class is [GameTicker](Source/Game-GameTicker.cppm).

To create a thread with a role, call `CreateThread()` on an instance of `PonyEngine::Application::IApplication`.
In params pass a thread function and `PonyEngine::Application::ThreadParams`. In params you set a role.
It must be either one of available thread roles or an empty string. The empty string means a default role, it's an equivalent to a normal thread creation.
To get a list of available thread roles, call `ThreadRoles()` on an instance of `PonyEngine::Application::IApplication`.
