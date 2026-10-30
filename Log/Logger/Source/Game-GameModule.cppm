export module Game:GameModule;

import std;

import PonyEngine.Application;
import PonyEngine.Log.Ext;
import PonyEngine.Utility;

import :GameLogger;

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
		std::unique_ptr<GameLogger> gameLogger;
	};
}

namespace Game
{
	void GameModule::StartUp(PonyEngine::Application::IModuleContext& context)
	{
		const PonyEngine::Application::IApplication& application = context.Application();
		const PonyEngine::Log::ILogService& logService = application.GetInterface<PonyEngine::Log::ILogService>();
		PonyEngine::Log::ILogHub& logHub = application.GetInterface<PonyEngine::Log::ILogHub>();

		auto scopeGuardFlag = PonyEngine::Utility::ScopeGuardFlag();

		gameLogger = std::make_unique<GameLogger>();
		const auto loggerScopeGuard = PonyEngine::Utility::ScopeGuard([&]() noexcept { gameLogger.reset(); }, scopeGuardFlag);
		logHub.AddLogger(*gameLogger);

		scopeGuardFlag.Release();

		logService.Log(PonyEngine::Log::LogType::Error, "Log test!"); // Just to show how it works.
	}

	void GameModule::ShutDown(PonyEngine::Application::IModuleContext& context)
	{
		PonyEngine::Log::ILogHub& logHub = context.Application().GetInterface<PonyEngine::Log::ILogHub>();
		logHub.RemoveLogger(*gameLogger);
		gameLogger.reset();
	}
}
