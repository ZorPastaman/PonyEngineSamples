export module Game:GameModule;

import std;

import PonyEngine.Application;

import :GameTicker;

export namespace Game
{
	class GameModule final : public PonyEngine::Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		GameModule() noexcept = default;
		GameModule(const GameModule&) = delete;
		GameModule(GameModule&&) = delete;

		~GameModule() noexcept = default;

		virtual void StartUp(PonyEngine::Application::IModuleContext& context) override;
		virtual void ShutDown(PonyEngine::Application::IModuleContext& context) override;

		GameModule& operator =(const GameModule&) = delete;
		GameModule& operator =(GameModule&&) = delete;

	private:
		std::unique_ptr<GameTicker> gameTicker;
	};
}

namespace Game
{
	void GameModule::StartUp(PonyEngine::Application::IModuleContext& context)
	{
		gameTicker = std::make_unique<GameTicker>(context.Application());
		context.AddTickable(gameTicker->Tickable(), PonyEngine::Application::TickableOrder{.beginOrder = 0, .tickOrder = 0});
	}

	void GameModule::ShutDown(PonyEngine::Application::IModuleContext& context)
	{
		context.RemoveTickable(gameTicker->Tickable(), PonyEngine::Application::TickableOrder{.beginOrder = 0, .tickOrder = 0});
		gameTicker.reset();
	}
}
