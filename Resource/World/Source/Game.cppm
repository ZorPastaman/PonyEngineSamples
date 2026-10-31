export module Game;

import std;

import PonyEngine.Application;
import PonyEngine.Async;
import PonyEngine.Log;
import PonyEngine.Resource.Pack;
import PonyEngine.World;
import PonyEngine.World.Hierarchy;
import PonyEngine.World.Meta;

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

		auto& packService = application.GetInterface<PonyEngine::Resource::Pack::IPackService>();
		const std::shared_ptr<PonyEngine::Resource::Pack::IPackMountRequest> packRequest = packService.MountPack("Packs/WorldPackManifest.bin", "Packs/WorldPackData.bin",
			PonyEngine::Resource::Pack::AccessType::Loadable);
		packRequest->Wait();

		auto& resourceService = application.GetInterface<PonyEngine::Resource::IResourceService>();
		const std::shared_ptr<PonyEngine::Resource::IResourceRequest> resourceRequest = resourceService.LoadResource(resourceService.MakeResourceID("World"));
		resourceRequest->Wait();
		const std::shared_ptr<const PonyEngine::World::WorldDefinition> worldDef = resourceRequest->Resource<PonyEngine::World::WorldDefinition>();

		auto& worldService = application.GetInterface<PonyEngine::World::IWorldService>();
		const std::shared_ptr<PonyEngine::World::IWorld> world = worldService.CreateWorld(*worldDef);

		std::array<PonyEngine::World::Entity, 2> nameEntities;
		std::array<PonyEngine::World::Meta::Name, 2> names;
		std::array<PonyEngine::World::Entity, 1> descriptionEntities;
		std::array<PonyEngine::World::Meta::Description, 1> descriptions;
		std::array<PonyEngine::World::Entity, 1> parentEntities;
		std::array<PonyEngine::World::Hierarchy::Parent*, 1> parents;
		std::array<PonyEngine::World::Entity, 2> transformEntities;
		std::array<PonyEngine::World::Hierarchy::LocalTransform3D, 2> transforms;
		std::array<PonyEngine::World::Entity, 1> flatTransformEntities;
		std::array<PonyEngine::World::Hierarchy::LocalTransform2D, 1> flatTransforms;
		world->GetComponents<PonyEngine::World::Meta::Name>(nameEntities, names);
		world->GetComponents<PonyEngine::World::Meta::Description>(descriptionEntities, descriptions);
		world->GetComponents<PonyEngine::World::Hierarchy::Parent>(parentEntities, parents);
		world->GetComponents<PonyEngine::World::Hierarchy::LocalTransform3D>(transformEntities, transforms);
		world->GetComponents<PonyEngine::World::Hierarchy::LocalTransform2D>(flatTransformEntities, flatTransforms);

		const std::string_view name0 = names[0].Get();
		const std::string_view name1 = names[1].Get();
		const std::string_view desc = *world->GetObject(descriptions[0].value).Get<const std::string_view>();

		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Name entities: '{}' and '{}'.", nameEntities[0].id, nameEntities[1].id);
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Names: '{}' and '{}'.", name0, name1);
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Description entity: '{}'.", descriptionEntities[0].id);
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Description: '{}'.", desc);
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Parent entity: '{}'; Child entity: '{}'.", parents[0]->value.id, parentEntities[0].id);
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "First Transform3D. Entity: '{}'; Position: '{}'; Rotation: '{}'; Scale: '{}'.",
			transformEntities[0].id, transforms[0].Position(), transforms[0].Rotation(), transforms[0].Scale());
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Second Transform3D. Entity: '{}'; Position: '{}'; Rotation: '{}'; Scale: '{}'.",
			transformEntities[1].id, transforms[1].Position(), transforms[1].Rotation(), transforms[1].Scale());
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Transform2D. Entity: '{}'; Position: '{}'; Rotation: '{}'; Scale: '{}'.",
			flatTransformEntities[0].id, flatTransforms[0].Position(), flatTransforms[0].Rotation(), flatTransforms[0].Scale());
	}

	void GameModule::ShutDown(PonyEngine::Application::IModuleContext& context)
	{
	}
}
