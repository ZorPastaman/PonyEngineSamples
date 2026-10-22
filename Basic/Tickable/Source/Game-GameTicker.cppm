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

		~GameTicker() noexcept;

		[[nodiscard("Pure function")]]
		PonyEngine::Application::ITickable& Tickable() noexcept;

		GameTicker& operator =(const GameTicker&) = delete;
		GameTicker& operator =(GameTicker&&) = delete;

	private:
		virtual void Begin() override;
		virtual void End() override;
		virtual void Tick() override;
	};
}

namespace Game
{
	GameTicker::GameTicker(PonyEngine::Application::IApplication& application) noexcept
	{
		// Add start-up logic here.
	}

	GameTicker::~GameTicker() noexcept
	{
		// Add shut-down logic here.
	}

	PonyEngine::Application::ITickable& GameTicker::Tickable() noexcept
	{
		return *this;
	}

	void GameTicker::Begin()
	{
		// Prepare for ticking.
	}

	void GameTicker::End()
	{
		// Clean up after ticking.
	}

	void GameTicker::Tick()
	{
		// Add tick logic here.
		// This is the place to update the state, process events, etc.
	}
}
