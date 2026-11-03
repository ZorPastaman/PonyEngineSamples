export module Game;

import std;

import PonyEngine.Application;
import PonyEngine.Log;
import PonyEngine.Math;
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
		struct Position final
		{
			PonyEngine::Math::Vector3<float> value;
		};
		struct Velocity final
		{
			PonyEngine::Math::Vector3<float> value;
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

		// Registering components.
		worldService.RegisterComponent<Position>();
		worldService.RegisterComponent<Velocity>();

		// Creating world.
		const std::shared_ptr<PonyEngine::World::IWorld> world = worldService.CreateWorld();

		// Creating entities.
		std::array<PonyEngine::World::Entity, 2> entities;
		world->CreateEntities(entities);
		for (std::size_t i = 0uz; i < entities.size(); ++i)
		{
			PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Created entity: '{}'.", entities[i].id);
		}

		// Adding components.
		std::array<Position, entities.size()> positions;
		std::array<Velocity, entities.size()> velocities;
		for (std::size_t i = 0uz; i < positions.size(); ++i)
		{
			for (std::size_t j = 0uz; j < PonyEngine::Math::Vector3<float>::ComponentCount; ++j)
			{
				positions[i].value[j] = static_cast<float>(i * 2 + j * 5);
				velocities[i].value[j] = static_cast<float>(i + j * 3);
			}
		}
		world->AddComponents<Position>(entities, positions);
		world->AddComponents<Velocity>(entities, velocities);
		for (std::size_t i = 0uz; i < entities.size(); ++i)
		{
			PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Position added. Entity: '{}'; Position: '{}'.", entities[i].id, positions[i].value);
			PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Velocity added. Entity: '{}'; Velocity: '{}'.", entities[i].id, velocities[i].value);
		}

		// Checking component counts.
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Position component count: '{}'.", world->CountComponents<Position>());
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Velocity component count: '{}'.", world->CountComponents<Velocity>());

		// Getting components.
		std::array<PonyEngine::World::Entity, entities.size()> positionEntities;
		std::array<Position, entities.size()> entityPositions;
		std::array<PonyEngine::World::Entity, entities.size()> velocityEntities;
		std::array<Velocity, entities.size()> entityVelocities;
		world->GetComponents<Position>(positionEntities, entityPositions);
		world->GetComponents<Velocity>(velocityEntities, entityVelocities);
		for (std::size_t i = 0uz; i < entities.size(); ++i)
		{
			PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Position gotten. Entity: '{}'; Position: '{}'.", positionEntities[i].id, entityPositions[i].value);
			PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Velocity gotten. Entity: '{}'; Velocity: '{}'.", velocityEntities[i].id, entityVelocities[i].value);
		}

		// Modifying components.
		for (std::size_t i = 0uz; i < entities.size(); ++i)
		{
			entityPositions[i].value += entityVelocities[i].value;
		}
		world->AddComponents<Position>(positionEntities, entityPositions); // If the component exists on entity, it will be overwritten.
		world->GetComponents<Position>(positionEntities, entityPositions);
		for (std::size_t i = 0uz; i < entities.size(); ++i)
		{
			PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Position after modifying. Entity: '{}'; Position: '{}'.", positionEntities[i].id, entityPositions[i].value);
		}

		// Modifying via pointers.
		std::array<Position*, entities.size()> positionPointers;
		std::array<Velocity*, entities.size()> velocityPointers;
		world->GetComponents<Position>(positionEntities, positionPointers);
		world->GetComponents<Velocity>(velocityEntities, velocityPointers);
		for (std::size_t i = 0uz; i < entities.size(); ++i)
		{
			positionPointers[i]->value += velocityPointers[i]->value;
		}
		// No need for adding components - they are already modified.
		world->GetComponents<Position>(positionEntities, entityPositions);
		for (std::size_t i = 0uz; i < entities.size(); ++i)
		{
			PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Position after modifying with pointers. Entity: '{}'; Position: '{}'.", positionEntities[i].id, entityPositions[i].value);
		}

		// Removing a component.
		world->RemoveComponent<Velocity>(entities[0]);
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Position component count after velocity removing: '{}'.", world->CountComponents<Position>());
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Velocity component count after velocity removing: '{}'.", world->CountComponents<Velocity>());

		// Dropping components.
		world->DropComponents<Position>();
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Position component count after dropping position: '{}'.", world->CountComponents<Position>());
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Velocity component count after dropping position: '{}'.", world->CountComponents<Velocity>());

		// Checking entities for validity before destroying them.
		std::array<bool, entities.size()> areValid;
		world->AreValid(entities, areValid);
		for (std::size_t i = 0uz; i < entities.size(); ++i)
		{
			PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Entity '{}' is valid: '{}'.", entities[i].id, areValid[i]);
		}

		// Destroying entities.
		world->DestroyEntities(entities);

		// Checking entities for validity after destroying them.
		world->AreValid(entities, areValid);
		for (std::size_t i = 0uz; i < entities.size(); ++i)
		{
			PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Entity '{}' is valid: '{}'.", entities[i].id, areValid[i]);
		}
	}

	void GameModule::ShutDown(PonyEngine::Application::IModuleContext& context)
	{
	}
}
