export module Game:GameTicker;

import std;

import PonyEngine.Application;
import PonyEngine.Job;
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

		PonyEngine::Log::ILogService* logService;
		PonyEngine::Job::IJobService* jobService;

		std::vector<double> values;
	};
}

namespace Game
{
	GameTicker::GameTicker(PonyEngine::Application::IApplication& application) noexcept :
		logService{&application.GetInterface<PonyEngine::Log::ILogService>()},
		jobService{&application.GetInterface<PonyEngine::Job::IJobService>()},
		values(10000)
	{
	}

	PonyEngine::Application::ITickable& GameTicker::Tickable() noexcept
	{
		return *this;
	}

	void GameTicker::Tick()
	{
		std::array<PonyEngine::Job::JobHandle, 2> calculationJobs;
		calculationJobs[0] = jobService->Schedule([values = std::span(values).subspan(0uz, values.size() / 2uz), ls = logService]() noexcept // Schedules a task.
		{
			PonyEngine::Log::LogToLogService(*ls, PonyEngine::Log::LogType::Info, "Calculating first half... Thread: '{}'.", std::this_thread::get_id());
			for (std::size_t i = 0uz; i < values.size(); ++i)
			{
				values[i] += static_cast<double>(i);
			}
			PonyEngine::Log::LogToLogService(*ls, PonyEngine::Log::LogType::Info, "Calculating first half done. Thread: '{}'.", std::this_thread::get_id());
		});
		calculationJobs[1] = jobService->Schedule([values = std::span(values).subspan(values.size() / 2uz, values.size() / 2uz), ls = logService]() noexcept // Schedules a task that may be executed parallelly to the first one.
		{
			PonyEngine::Log::LogToLogService(*ls, PonyEngine::Log::LogType::Info, "Calculating second half... Thread: '{}'.", std::this_thread::get_id());
			for (std::size_t i = 0uz; i < values.size(); ++i)
			{
				values[i] += static_cast<double>(i) * 3.;
			}
			PonyEngine::Log::LogToLogService(*ls, PonyEngine::Log::LogType::Info, "Calculating second half done. Thread: '{}'.", std::this_thread::get_id());
		});
		double average = 0.;
		const PonyEngine::Job::JobHandle averageJob = jobService->Schedule([&]() noexcept // Schedules a task that may be executed only when the previous tasks are finished.
		{
			PonyEngine::Log::LogToLogService(*logService, PonyEngine::Log::LogType::Info, "Calculating average... Thread: '{}'.", std::this_thread::get_id());
			for (const double value : values)
			{
				average += value / values.size();
			}
			PonyEngine::Log::LogToLogService(*logService, PonyEngine::Log::LogType::Info, "Calculating average done. Thread: '{}'.", std::this_thread::get_id());
		}, PonyEngine::Job::JobParams{.dependencies = calculationJobs}); // Pass dependencies to prevent the task from early execution.
		
		if (!jobService->IsCompleted(averageJob)) // Checks if the task is completed.
		{
			jobService->Wait(averageJob); // Waits till the task is completed.
		}

		PonyEngine::Log::LogToLogService(*logService, PonyEngine::Log::LogType::Info, "Average value: '{}'.", average);
	}
}
