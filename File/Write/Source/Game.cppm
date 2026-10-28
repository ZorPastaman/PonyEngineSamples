export module Game;

import std;

import PonyEngine.Application;
import PonyEngine.Async;
import PonyEngine.File;
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
		PonyEngine::Log::ILogService& logService = application.GetInterface<PonyEngine::Log::ILogService>();
		PonyEngine::File::IFileService& fileService = application.GetInterface<PonyEngine::File::IFileService>();
		const auto filePath = (application.TempDataDirectory() / "Text/Sample.txt").lexically_normal();
		std::filesystem::create_directories(filePath.parent_path());
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Sample file path: '{}'.", filePath.string());
		const std::shared_ptr<PonyEngine::File::IFile> file = fileService.OpenFile(filePath, PonyEngine::File::FileParams::WriteTruncate()); // Opening a file for writing. It truncates a file if it already exists.

		constexpr std::string_view firstLine = "It's a sample file.\n";
		const std::shared_ptr<PonyEngine::File::IWriteRequest> firstRequest = file->Write(PonyEngine::File::WriteParams
		{
			.buffer = std::span(reinterpret_cast<const std::byte*>(firstLine.data()), firstLine.size()), // Target buffer.
			.offset = 0uz // File offset in bytes.
		});
		firstRequest->Cancel(); // Request can be canceled. But they still may finish with success or failure.
		firstRequest->Wait(); // Waits for the operation to finish.
		switch (firstRequest->Status()) // Check the request status and act accordingly.
		{
		case PonyEngine::Async::RequestStatus::Success:
			PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "First request success. Read bytes: '{}'.", firstRequest->ByteCount()); // ByteCount() is available only on success.
			break;
		case PonyEngine::Async::RequestStatus::Failure:
			PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Error, firstRequest->Exception(), "First request failure."); // Exception() is available only on failure.
			break;
		case PonyEngine::Async::RequestStatus::Canceled:
			PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "First request canceled.");
			break;
		default:
			break;
		}

		std::atomic_bool finished = false;
		constexpr std::string_view secondLine = "It's written by a sample module.\n";
		const std::shared_ptr<PonyEngine::File::IWriteRequest> secondRequest = file->Write(PonyEngine::File::WriteParams
		{
			.buffer = std::span(reinterpret_cast<const std::byte*>(secondLine.data()), secondLine.size()),
			.offset = firstLine.size()
		}, [&](const PonyEngine::File::IWriteRequest& request) noexcept // You can pass a callback function as well.
		{                                                               // Attention: it will be called on an io thread.
			switch (request.Status())
			{
			case PonyEngine::Async::RequestStatus::Success:
				PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Second request success. Read bytes: '{}'.", request.ByteCount());
				break;
			case PonyEngine::Async::RequestStatus::Failure:
				PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Error, request.Exception(), "Second request failure.");
				break;
			case PonyEngine::Async::RequestStatus::Canceled:
				PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Second request canceled.");
				break;
			default:
				break;
			}

			finished.store(true, std::memory_order::relaxed);
			finished.notify_one();
		});

		finished.wait(false, std::memory_order::relaxed);
	}

	void GameModule::ShutDown(PonyEngine::Application::IModuleContext& context)
	{
	}
}
