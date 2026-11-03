export module Game:GameModule;

import std;

import PonyEngine.Application;
import PonyEngine.Utility;

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
		auto scopeGuardFlag = PonyEngine::Utility::ScopeGuardFlag();

		gameTicker = std::make_unique<GameTicker>(context.Application());
		const auto tickerScopeGuard = PonyEngine::Utility::ScopeGuard([&]() noexcept { gameTicker.reset(); }, scopeGuardFlag);
		context.AddTickable(gameTicker->Tickable(), PonyEngine::Application::TickableOrder{.tickOrder = 0});

		scopeGuardFlag.Release();
	}

	void GameModule::ShutDown(PonyEngine::Application::IModuleContext& context)
	{
		context.RemoveTickable(gameTicker->Tickable(), PonyEngine::Application::TickableOrder{.tickOrder = 0});
		gameTicker.reset();
	}
}
