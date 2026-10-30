export module Game:GameLogger;

import std;

import PonyEngine.Log.Ext;

export namespace Game
{
	class GameLogger final : public PonyEngine::Log::ILogger
	{
	public:
		[[nodiscard("Pure constructor")]]
		GameLogger() noexcept = default;
		GameLogger(const GameLogger&) = delete;
		GameLogger(GameLogger&&) = delete;

		~GameLogger() noexcept = default;

		virtual void Log(std::string_view formattedMessage, const PonyEngine::Log::LogEntry& logEntry) noexcept override;

		GameLogger& operator =(const GameLogger&) = delete;
		GameLogger& operator =(GameLogger&&) = delete;
	};
}

namespace Game
{
	void GameLogger::Log(const std::string_view formattedMessage, const PonyEngine::Log::LogEntry& logEntry) noexcept
	{
		std::println("It's a log from the game logger. Formatted message:\n{}Original message: {}\nLog type: {}", formattedMessage, logEntry.message, logEntry.logType);
	}
}
