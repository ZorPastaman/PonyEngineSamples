export module Game;

import std;

import PonyEngine.Application;
import PonyEngine.Log;
import PonyEngine.World;

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
		class ObjectSample final
		{
		public:
			[[nodiscard("Pure constructor")]]
			explicit ObjectSample(const PonyEngine::Log::ILogService& logService) noexcept;
			[[nodiscard("Pure constructor")]]
			ObjectSample(const ObjectSample& other) noexcept = default;
			[[nodiscard("Pure constructor")]]
			ObjectSample(ObjectSample&& other) noexcept = default;

			~ObjectSample() noexcept;

			ObjectSample& operator =(const ObjectSample& other) noexcept = default;
			ObjectSample& operator =(ObjectSample&& other) noexcept = default;

		private:
			const PonyEngine::Log::ILogService* logService;
		};

		struct ObjectWrapper final
		{
			PonyEngine::World::ObjectHandle<ObjectSample> object;
		};
	};
}

namespace Game
{
	void GameModule::StartUp(PonyEngine::Application::IModuleContext& context)
	{
		PonyEngine::Application::IApplication& application = context.Application();
		PonyEngine::Log::ILogService& logService = application.GetInterface<PonyEngine::Log::ILogService>();
		PonyEngine::World::IWorldService& worldService = application.GetInterface<PonyEngine::World::IWorldService>();

		// Registering component and object handle member.
		// Object handle member is used on garbage collection.
		worldService.RegisterComponent<ObjectWrapper>();
		worldService.RegisterObjectHandleMember(&ObjectWrapper::object);

		// Creating world.
		const std::shared_ptr<PonyEngine::World::IWorld> world = worldService.CreateWorld();

		// Creating entities.
		std::array<PonyEngine::World::Entity, 2> entities;
		world->CreateEntities(entities);

		// Creating objects and adding them to components on the entities.
		world->AddComponent<ObjectWrapper>(entities[0], ObjectWrapper{.object = world->RegisterObject(std::make_shared<ObjectSample>(logService))});
		world->AddComponent<ObjectWrapper>(entities[1], ObjectWrapper{.object = world->RegisterObject(std::make_shared<ObjectSample>(logService)) });

		// Getting components.
		ObjectWrapper wrapper;
		world->TryGetComponent(entities[0], wrapper);
		const PonyEngine::World::ObjectHandle<ObjectSample> object0Handle = wrapper.object;
		world->TryGetComponent(entities[1], wrapper);
		const PonyEngine::World::ObjectHandle<ObjectSample> object1Handle = wrapper.object;

		// Getting world objects and getting our objects from them.
		const PonyEngine::World::Object& object0 = world->GetObject(object0Handle);
		const PonyEngine::World::Object& object1 = world->GetObject(object1Handle);
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Object 0 is at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(object0.Get<ObjectSample>()));
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Object 1 is at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(object1.Get<ObjectSample>()));

		// Destroying one entity.
		// Both objects will be alive.
		world->DestroyEntity(entities[0]);
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Is object 0 alive: '{}'.", world->IsObjectValid(object0Handle));
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Is object 1 alive: '{}'.", world->IsObjectValid(object1Handle));

		// The first object will be destroyed on the garbage collection.
		world->CollectGarbage();
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Is object 0 alive: '{}'.", world->IsObjectValid(object0Handle));
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Is object 1 alive: '{}'.", world->IsObjectValid(object1Handle));
	}

	void GameModule::ShutDown(PonyEngine::Application::IModuleContext& context)
	{
	}

	GameModule::ObjectSample::ObjectSample(const PonyEngine::Log::ILogService& logService) noexcept :
		logService{&logService}
	{
		PonyEngine::Log::LogToLogService(*this->logService, PonyEngine::Log::LogType::Info, "Object at '0x{:X}' created.", reinterpret_cast<std::uintptr_t>(this));
	}

	GameModule::ObjectSample::~ObjectSample() noexcept
	{
		PonyEngine::Log::LogToLogService(*logService, PonyEngine::Log::LogType::Info, "Object at '0x{:X}' destroyed.", reinterpret_cast<std::uintptr_t>(this));
	}
}
