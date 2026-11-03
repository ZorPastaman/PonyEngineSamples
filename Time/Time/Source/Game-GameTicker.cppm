export module Game:GameTicker;

import std;

import PonyEngine.Application;
import PonyEngine.Log;
import PonyEngine.Time;

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
		PonyEngine::Log::ILogService* logService;
		PonyEngine::Time::ITimeService* timeService;
	};
}

namespace Game
{
	GameTicker::GameTicker(PonyEngine::Application::IApplication& application) noexcept :
		application{&application},
		logService{&this->application->GetInterface<PonyEngine::Log::ILogService>()},
		timeService{&this->application->GetInterface<PonyEngine::Time::ITimeService>()}
	{
		PonyEngine::Log::LogToLogService(*logService, PonyEngine::Log::LogType::Info, "Initial time service params. Cap: '{}'; Scale: '{}'; Step: '{}'.", 
			timeService->DeltaTimeCapSeconds(), timeService->TimeScale(), timeService->StepPeriodSeconds());
	}

	PonyEngine::Application::ITickable& GameTicker::Tickable() noexcept
	{
		return *this;
	}

	void GameTicker::Tick()
	{
		const std::uint64_t frame = application->FrameCount();
		const double applicationDeltaTime = application->DeltaTimeSeconds();
		const double realDeltaTime = timeService->RealDeltaTimeSeconds();
		const double virtualDeltaTime = timeService->VirtualDeltaTimeSeconds();
		const double unscaledVirtualDeltaTime = timeService->UnscaledVirtualDeltaTimeSeconds();
		const std::uint64_t realDeltaStep = timeService->RealDeltaStepCount();
		const std::uint64_t virtualDeltaStep = timeService->VirtualDeltaStepCount();
		const std::uint64_t unscaledVirtualDeltaStep = timeService->UnscaledVirtualDeltaStepCount();
		PonyEngine::Log::LogToLogService(*logService, PonyEngine::Log::LogType::Info, "Sample time info. Frame: '{}'.", frame);
		PonyEngine::Log::LogToLogService(*logService, PonyEngine::Log::LogType::Info, "Application delta time: '{}'.", applicationDeltaTime);
		PonyEngine::Log::LogToLogService(*logService, PonyEngine::Log::LogType::Info, "Real delta time: '{}'; Virtual delta time: '{}'; Unscaled virtual delta time: '{}'.",
			realDeltaTime, virtualDeltaTime, unscaledVirtualDeltaTime);
		PonyEngine::Log::LogToLogService(*logService, PonyEngine::Log::LogType::Info, "Real delta step: '{}'; Virtual delta step: '{}'; Unscaled virtual delta step: '{}'.",
			realDeltaStep, virtualDeltaStep, unscaledVirtualDeltaStep);

		if (frame == 20ull)
		{
			constexpr double step = 0.0001;
			PonyEngine::Log::LogToLogService(*logService, PonyEngine::Log::LogType::Info, "Setting time step to '{}'.", step);
			timeService->StepPeriodSeconds(step);
		}
		else if (frame == 40ull)
		{
			constexpr double scale = 2.5;
			PonyEngine::Log::LogToLogService(*logService, PonyEngine::Log::LogType::Info, "Setting time scale to '{}'.", scale);
			timeService->TimeScale(scale);
		}
		else if (frame == 60ull)
		{
			constexpr double cap = 0.00001;
			PonyEngine::Log::LogToLogService(*logService, PonyEngine::Log::LogType::Info, "Setting time cap to '{}'.", cap);
			timeService->DeltaTimeCapSeconds(cap);
		}
		else if (frame == 80ull)
		{
			application->Stop();
		}
	}
}
