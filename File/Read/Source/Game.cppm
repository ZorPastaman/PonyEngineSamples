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
		const auto filePath = (application.ExecutableDirectory() / "Data/Sample.txt").lexically_normal();
		const std::shared_ptr<PonyEngine::File::IFile> file = fileService.OpenFile(filePath, PonyEngine::File::FileParams::Read()); // Opening a file by path for reading.

		auto firstLine = std::string(); // Preparing a buffer for the read content.
		firstLine.resize(19);
		const std::shared_ptr<PonyEngine::File::IReadRequest> firstRequest = file->Read(PonyEngine::File::ReadParams
		{
			.buffer = std::span(reinterpret_cast<std::byte*>(firstLine.data()), firstLine.size()), // Target buffer.
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
		auto secondLine = std::string();
		secondLine.resize(29);
		const std::shared_ptr<PonyEngine::File::IReadRequest> secondRequest = file->Read(PonyEngine::File::ReadParams
		{
			.buffer = std::span(reinterpret_cast<std::byte*>(secondLine.data()), secondLine.size()),
			.offset = 20uz
		}, [&](const PonyEngine::File::IReadRequest& request) noexcept // You can pass a callback function as well.
		{                                                              // Attention: it will be called on an io thread.
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
