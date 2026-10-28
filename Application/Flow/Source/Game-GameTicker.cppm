export module Game:GameTicker;

import std;

import PonyEngine.Application;
import PonyEngine.Log;

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

		double position;
		double speed;
	};
}

namespace Game
{
	GameTicker::GameTicker(PonyEngine::Application::IApplication& application) noexcept :
		application{&application},
		logService{&this->application->GetInterface<PonyEngine::Log::ILogService>()},
		position{0.},
		speed{2.}
	{
	}

	PonyEngine::Application::ITickable& GameTicker::Tickable() noexcept
	{
		return *this;
	}

	void GameTicker::Tick()
	{
		const double prevPosition = position;
		position += speed * application->DeltaTimeSeconds(); // Usage of delta time in seconds
		PonyEngine::Log::LogToLogService(*logService, PonyEngine::Log::LogType::Info, "Position: '{}'. Delta: '{}'.", position, position - prevPosition);

		const std::uint64_t frame = application->FrameCount(); // Getting a current frame count.
		const double targetFrameTime = application->TargetFrameTimeSeconds(); // Getting a current target frame time in seconds.
		if (frame == 20ull)
		{
			PonyEngine::Log::LogToLogService(*logService, PonyEngine::Log::LogType::Info, "Changing target frame time from '{}' to '{}'.", targetFrameTime, 1./60.);
			application->TargetFrameTimeSeconds(1./60.); // Changing frame frequency to 60 Hz.
		}
		else if (frame == 40ull)
		{
			PonyEngine::Log::LogToLogService(*logService, PonyEngine::Log::LogType::Info, "Changing target frame time from '{}' to '{}'.", targetFrameTime, 1./80.);
			application->TargetFrameTimeSeconds(1./80.); // Changing frame frequency to 80 Hz.
		}
		else if (frame == 60ull)
		{
			PonyEngine::Log::LogToLogService(*logService, PonyEngine::Log::LogType::Info, "Changing target frame time from '{}' to '{}'.", targetFrameTime, 0.);
			application->TargetFrameTimeSeconds(0.); // Changing frame frequency to 0 which means unrestricted.
		}
		else if (frame == 80ull)
		{
			application->Stop(); // Stops the application. It will close the process in the end of the frame.
		}
	}
}
