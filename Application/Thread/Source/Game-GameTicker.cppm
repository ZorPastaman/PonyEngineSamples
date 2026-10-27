export module Game:GameTicker;

import std;

import PonyEngine.Application;

export namespace Game
{
	class GameTicker final : private PonyEngine::Application::ITickable
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit GameTicker(PonyEngine::Application::IApplication& application) noexcept;
		GameTicker(const GameTicker&) = delete;
		GameTicker(GameTicker&&) = delete;

		~GameTicker() noexcept = default;

		[[nodiscard("Pure function")]]
		PonyEngine::Application::ITickable& Tickable() noexcept;

		GameTicker& operator =(const GameTicker&) = delete;
		GameTicker& operator =(GameTicker&&) = delete;

	private:
		virtual void Tick() override;

		PonyEngine::Application::IApplication* application;
	};
}

namespace Game
{
	GameTicker::GameTicker(PonyEngine::Application::IApplication& application) noexcept :
		application{&application}
	{
	}

	PonyEngine::Application::ITickable& GameTicker::Tickable() noexcept
	{
		return *this;
	}

	void GameTicker::Tick()
	{
		const std::span<const std::string_view> threadRoles = application->ThreadRoles(); // Gets all the possible thread roles.
		int someValue = 0;

		if (std::ranges::contains(threadRoles, "Main"))
		{
			std::thread anotherThread = application->CreateThread([&]() // Thread function.
			{
				++someValue;
			}, PonyEngine::Application::ThreadParams
			{
				.role = "Main" // Applied a main role to the thread. It applies some priority to the thread.
			});
			anotherThread.join();
		}

		std::thread defaultThread = application->CreateThread([&]()
		{
			++someValue;
		}, PonyEngine::Application::ThreadParams
		{
			.role = "" // Default role (no priority applied) is always available though it's not included in application->ThreadRoles()
		});
		defaultThread.join();
	}
}
