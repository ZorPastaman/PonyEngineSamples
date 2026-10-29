module;

#include "PonyEngine/Log/Log.h"

export module Game;

import std;

import PonyEngine.Application;
import PonyEngine.Log;

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
	};
}

namespace Game
{
	void GameModule::StartUp(PonyEngine::Application::IModuleContext& context)
	{
		const PonyEngine::Application::IApplication& application = context.Application();
		const PonyEngine::Log::ILogService& logService = application.GetInterface<PonyEngine::Log::ILogService>();
		const PonyEngine::Log::ILogService* const logServicePtr = &logService;
		const PonyEngine::Log::ILogService* const logServiceNull = nullptr;

		constexpr int dummy = 3;

		// Logging directly to the log service.
		logService.Log(PonyEngine::Log::LogType::Verbose, "It's a simple message.");
		logService.Log(PonyEngine::Log::LogType::Debug, "It's a formatted message. Arg: '{}'.", std::make_format_args(dummy));
		logService.Log(PonyEngine::Log::LogType::Info, "It's a simple message with a stacktrace.", std::stacktrace::current());
		logService.Log(PonyEngine::Log::LogType::Warning, "It's a formatted message with a stacktrace. Arg: '{}'.", std::make_format_args(dummy), std::stacktrace::current());
		try
		{
			throw std::runtime_error("Test exception");
		}
		catch (...)
		{
			logService.Log(PonyEngine::Log::LogType::Error, std::current_exception());
			logService.Log(PonyEngine::Log::LogType::Fatal, std::current_exception(), "It's a simple message with an exception.");
			logService.Log(PonyEngine::Log::LogType::Error, std::current_exception(), "It's a formatted message with an exception. Arg: '{}'.", std::make_format_args(dummy));
			logService.Log(PonyEngine::Log::LogType::Warning, std::current_exception(), std::stacktrace::current());
			logService.Log(PonyEngine::Log::LogType::Info, std::current_exception(), "It's a simple message with an exception and a stacktrace.", std::stacktrace::current());
			logService.Log(PonyEngine::Log::LogType::Debug, std::current_exception(), "It's a formatted message with an exception and a stacktrace. Arg: '{}'.", std::make_format_args(dummy), std::stacktrace::current());
		}

		// Logging via a helper function via a reference to a logger.
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Verbose, "It's a simple message.");
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Debug, "It's a formatted message. Arg: '{}'.", dummy);
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, std::stacktrace::current(), "It's a simple message with a stacktrace.");
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Warning, std::stacktrace::current(), "It's a formatted message with a stacktrace. Arg: '{}'.", dummy);
		try
		{
			throw std::runtime_error("Test exception");
		}
		catch (...)
		{
			PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Error, std::current_exception());
			PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Fatal, std::current_exception(), "It's a simple message with an exception.");
			PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Error, std::current_exception(), "It's a formatted message with an exception. Arg: '{}'.", dummy);
			PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Warning, std::stacktrace::current(), std::current_exception());
			PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, std::stacktrace::current(), std::current_exception(), "It's a simple message with an exception and a stacktrace.");
			PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Debug, std::stacktrace::current(), std::current_exception(), "It's a formatted message with an exception and a stacktrace. Arg: '{}'.", dummy);
		}

		// Logging via a helper function via a pointer to a logger.
		PonyEngine::Log::LogToLogService(logServicePtr, PonyEngine::Log::LogType::Verbose, "It's a simple message.");
		PonyEngine::Log::LogToLogService(logServicePtr, PonyEngine::Log::LogType::Debug, "It's a formatted message. Arg: '{}'.", dummy);
		PonyEngine::Log::LogToLogService(logServicePtr, PonyEngine::Log::LogType::Info, std::stacktrace::current(), "It's a simple message with a stacktrace.");
		PonyEngine::Log::LogToLogService(logServicePtr, PonyEngine::Log::LogType::Warning, std::stacktrace::current(), "It's a formatted message with a stacktrace. Arg: '{}'.", dummy);
		try
		{
			throw std::runtime_error("Test exception");
		}
		catch (...)
		{
			PonyEngine::Log::LogToLogService(logServicePtr, PonyEngine::Log::LogType::Error, std::current_exception());
			PonyEngine::Log::LogToLogService(logServicePtr, PonyEngine::Log::LogType::Fatal, std::current_exception(), "It's a simple message with an exception.");
			PonyEngine::Log::LogToLogService(logServicePtr, PonyEngine::Log::LogType::Error, std::current_exception(), "It's a formatted message with an exception. Arg: '{}'.", dummy);
			PonyEngine::Log::LogToLogService(logServicePtr, PonyEngine::Log::LogType::Warning, std::stacktrace::current(), std::current_exception());
			PonyEngine::Log::LogToLogService(logServicePtr, PonyEngine::Log::LogType::Info, std::stacktrace::current(), std::current_exception(), "It's a simple message with an exception and a stacktrace.");
			PonyEngine::Log::LogToLogService(logServicePtr, PonyEngine::Log::LogType::Debug, std::stacktrace::current(), std::current_exception(), "It's a formatted message with an exception and a stacktrace. Arg: '{}'.", dummy);
		}

		// Logging via a helper function via a nullptr pointer to a logger. No logging happens. The functions return immediately.
		PonyEngine::Log::LogToLogService(logServiceNull, PonyEngine::Log::LogType::Verbose, "It's a simple message.");
		PonyEngine::Log::LogToLogService(logServiceNull, PonyEngine::Log::LogType::Debug, "It's a formatted message. Arg: '{}'.", dummy);
		PonyEngine::Log::LogToLogService(logServiceNull, PonyEngine::Log::LogType::Info, std::stacktrace::current(), "It's a simple message with a stacktrace.");
		PonyEngine::Log::LogToLogService(logServiceNull, PonyEngine::Log::LogType::Warning, std::stacktrace::current(), "It's a formatted message with a stacktrace. Arg: '{}'.", dummy);
		try
		{
			throw std::runtime_error("Test exception");
		}
		catch (...)
		{
			PonyEngine::Log::LogToLogService(logServiceNull, PonyEngine::Log::LogType::Error, std::current_exception());
			PonyEngine::Log::LogToLogService(logServiceNull, PonyEngine::Log::LogType::Fatal, std::current_exception(), "It's a simple message with an exception.");
			PonyEngine::Log::LogToLogService(logServiceNull, PonyEngine::Log::LogType::Error, std::current_exception(), "It's a formatted message with an exception. Arg: '{}'.", dummy);
			PonyEngine::Log::LogToLogService(logServiceNull, PonyEngine::Log::LogType::Warning, std::stacktrace::current(), std::current_exception());
			PonyEngine::Log::LogToLogService(logServiceNull, PonyEngine::Log::LogType::Info, std::stacktrace::current(), std::current_exception(), "It's a simple message with an exception and a stacktrace.");
			PonyEngine::Log::LogToLogService(logServiceNull, PonyEngine::Log::LogType::Debug, std::stacktrace::current(), std::current_exception(), "It's a formatted message with an exception and a stacktrace. Arg: '{}'.", dummy);
		}

		// Logging via a helper macro via a reference to a logger. Some logs may be disabled based on a build type. Stacktrace capturing is dependent on a log type and a build type as well.
		PONY_LOG(logService, PonyEngine::Log::LogType::Info, "It's a simple message.");
		PONY_LOG(logService, PonyEngine::Log::LogType::Warning, "It's a formatted message. Arg: '{}'.", dummy);
		try
		{
			throw std::runtime_error("Test exception");
		}
		catch (...)
		{
			PONY_LOG(logService, PonyEngine::Log::LogType::Error, std::current_exception());
			PONY_LOG(logService, PonyEngine::Log::LogType::Fatal, std::current_exception(), "It's a simple message with an exception.");
			PONY_LOG(logService, PonyEngine::Log::LogType::Error, std::current_exception(), "It's a formatted message with an exception. Arg: '{}'.", dummy);
		}

		// Logging via a helper macro via a pointer to a logger. Some logs may be disabled based on a build type. Stacktrace capturing is dependent on a log type and a build type as well.
		PONY_LOG(logServicePtr, PonyEngine::Log::LogType::Info, "It's a simple message.");
		PONY_LOG(logServicePtr, PonyEngine::Log::LogType::Warning, "It's a formatted message. Arg: '{}'.", dummy);
		try
		{
			throw std::runtime_error("Test exception");
		}
		catch (...)
		{
			PONY_LOG(logServicePtr, PonyEngine::Log::LogType::Error, std::current_exception());
			PONY_LOG(logServicePtr, PonyEngine::Log::LogType::Fatal, std::current_exception(), "It's a simple message with an exception.");
			PONY_LOG(logServicePtr, PonyEngine::Log::LogType::Error, std::current_exception(), "It's a formatted message with an exception. Arg: '{}'.", dummy);
		}

		// Logging via a helper macro via a nullptr pointer to a logger. Some logs may be disabled based on a build type. Stacktrace capturing is dependent on a log type and a build type as well.
		PONY_LOG(logServicePtr, PonyEngine::Log::LogType::Info, "It's a simple message.");
		PONY_LOG(logServicePtr, PonyEngine::Log::LogType::Warning, "It's a formatted message. Arg: '{}'.", dummy);
		try
		{
			throw std::runtime_error("Test exception");
		}
		catch (...)
		{
			PONY_LOG(logServicePtr, PonyEngine::Log::LogType::Error, std::current_exception());
			PONY_LOG(logServicePtr, PonyEngine::Log::LogType::Fatal, std::current_exception(), "It's a simple message with an exception.");
			PONY_LOG(logServicePtr, PonyEngine::Log::LogType::Error, std::current_exception(), "It's a formatted message with an exception. Arg: '{}'.", dummy);
		}
	}

	void GameModule::ShutDown(PonyEngine::Application::IModuleContext& context)
	{
	}
}
