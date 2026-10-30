export module Game;

import std;

import PonyEngine.Application;
import PonyEngine.Async;
import PonyEngine.Log;
import PonyEngine.Resource.Pack;

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
		PonyEngine::Application::IApplication& application = context.Application();
		const PonyEngine::Log::ILogService& logService = application.GetInterface<PonyEngine::Log::ILogService>();

		// First, you need to mount a pack where the resource is placed.
		auto& packService = application.GetInterface<PonyEngine::Resource::Pack::IPackService>();
		const auto packManifestPath = std::filesystem::path("Packs/TextPackManifest.bin").lexically_normal();
		const auto packDataPath = std::filesystem::path("Packs/TextPackData.bin").lexically_normal();
		const std::shared_ptr<PonyEngine::Resource::Pack::IPackMountRequest> packRequest = packService.MountPack(packManifestPath, packDataPath,
			PonyEngine::Resource::Pack::AccessType::Loadable, [&](const PonyEngine::Resource::Pack::IPackMountRequest&) noexcept
			{
				logService.Log(PonyEngine::Log::LogType::Info, "Pack mounted.");
			});
		packRequest->Wait();

		// Then, you may make a load request.
		auto& resourceService = application.GetInterface<PonyEngine::Resource::IResourceService>();
		const std::shared_ptr<PonyEngine::Resource::IResourceRequest> resourceRequest = resourceService.LoadResource<std::string_view>(resourceService.MakeResourceID("Text"),
			[&](const PonyEngine::Resource::IResourceRequest&) noexcept
			{
				logService.Log(PonyEngine::Log::LogType::Info, "Resource loaded.");
			});
		resourceRequest->Wait();
		// Finally, you may get a resource from the request.
		const std::shared_ptr<const std::string_view> text = resourceRequest->Resource<std::string_view>();

		logService.Log(PonyEngine::Log::LogType::Info, *text);
	}

	void GameModule::ShutDown(PonyEngine::Application::IModuleContext& context)
	{
	}
}
