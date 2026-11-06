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
		struct Rotation final
		{
			PonyEngine::Math::Quaternion<float> value;
		};
		struct LinearVelocity final
		{
			PonyEngine::Math::Vector3<float> value;
		};
		struct AngularVelocity final
		{
			PonyEngine::Math::Quaternion<float> value;
		};
		struct Immovable final
		{
		};
		struct Nonrotatable final
		{
		};
		struct Scale final
		{
			float value;
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
		worldService.RegisterComponent<Rotation>();
		worldService.RegisterComponent<LinearVelocity>();
		worldService.RegisterComponent<AngularVelocity>();
		worldService.RegisterComponent<Immovable>();
		worldService.RegisterComponent<Nonrotatable>();
		worldService.RegisterComponent<Scale>();

		// Creating world and filling it with different components on different entities.
		const std::shared_ptr<PonyEngine::World::IWorld> world = worldService.CreateWorld();

		Position position;
		Rotation rotation;
		LinearVelocity linearVelocity;
		AngularVelocity angularVelocity;
		Scale scale;
		PonyEngine::World::Entity entity;
		std::array<PonyEngine::World::Entity, 6> entities;
		world->CreateEntities(entities);

		entity = entities[0];
		position.value = PonyEngine::Math::Vector3<float>(3.f, -1.f, 2.f);
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Adding position '{}' to entity '{}'.", position.value, entity.id);
		world->AddComponent<Position>(entity, position);

		entity = entities[1];
		position.value = PonyEngine::Math::Vector3<float>(4.f, -5.f, -2.f);
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Adding position '{}' to entity '{}'.", position.value, entity.id);
		world->AddComponent<Position>(entity, position);
		linearVelocity.value = PonyEngine::Math::Vector3<float>(1.f, -2.f, 3.f);
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Adding linear velocity '{}' to entity '{}'.", linearVelocity.value, entity.id);
		world->AddComponent<LinearVelocity>(entity, linearVelocity);

		entity = entities[2];
		position.value = PonyEngine::Math::Vector3<float>(14.f, -51.f, 2.f);
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Adding position '{}' to entity '{}'.", position.value, entity.id);
		world->AddComponent<Position>(entity, position);
		linearVelocity.value = PonyEngine::Math::Vector3<float>(-1.f, 2.f, 3.f);
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Adding linear velocity '{}' to entity '{}'.", linearVelocity.value, entity.id);
		world->AddComponent<LinearVelocity>(entity, linearVelocity);
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Adding immovable to entity '{}'.", entity.id);
		world->AddComponent<Immovable>(entity);

		entity = entities[3];
		position.value = PonyEngine::Math::Vector3<float>(1.f, 5.f, 2.f);
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Adding position '{}' to entity '{}'.", position.value, entity.id);
		world->AddComponent<Position>(entity, position);
		linearVelocity.value = PonyEngine::Math::Vector3<float>(-1.f, 2.f, 13.f);
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Adding linear velocity '{}' to entity '{}'.", linearVelocity.value, entity.id);
		world->AddComponent<LinearVelocity>(entity, linearVelocity);
		scale.value = 3.f;
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Adding scale '{}' to entity '{}'.", scale.value, entity.id);
		world->AddComponent<Scale>(entity, scale);

		entity = entities[4];
		position.value = PonyEngine::Math::Vector3<float>(14.f, -51.f, 2.f);
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Adding position '{}' to entity '{}'.", position.value, entity.id);
		world->AddComponent<Position>(entity, position);
		rotation.value = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-3.1f, 0.1f, 0.8f));
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Adding rotation '{}' to entity '{}'.", rotation.value, entity.id);
		world->AddComponent<Rotation>(entity, rotation);
		linearVelocity.value = PonyEngine::Math::Vector3<float>(-1.f, 2.f, 3.f);
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Adding linear velocity '{}' to entity '{}'.", linearVelocity.value, entity.id);
		world->AddComponent<LinearVelocity>(entity, linearVelocity);
		angularVelocity.value = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(2.f, -1.f, 0.5f));
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Adding linear velocity '{}' to entity '{}'.", linearVelocity.value, entity.id);
		world->AddComponent<AngularVelocity>(entity, angularVelocity);

		entity = entities[5];
		position.value = PonyEngine::Math::Vector3<float>(5.f, -12.f, -7.f);
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Adding position '{}' to entity '{}'.", position.value, entity.id);
		world->AddComponent<Position>(entity, position);
		rotation.value = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(-0.1f, 1.1f, 2.8f));
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Adding rotation '{}' to entity '{}'.", rotation.value, entity.id);
		world->AddComponent<Rotation>(entity, rotation);
		linearVelocity.value = PonyEngine::Math::Vector3<float>(-3.f, 1.f, 2.f);
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Adding linear velocity '{}' to entity '{}'.", linearVelocity.value, entity.id);
		world->AddComponent<LinearVelocity>(entity, linearVelocity);
		angularVelocity.value = PonyEngine::Math::RotationQuaternion(PonyEngine::Math::Vector3<float>(1.f, -1.f, 0.9f));
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Adding linear velocity '{}' to entity '{}'.", linearVelocity.value, entity.id);
		world->AddComponent<AngularVelocity>(entity, angularVelocity);
		PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Adding nonrotatable to entity '{}'.", entity.id);
		world->AddComponent<Nonrotatable>(entity);

		// Applies an angular velocity to an entity with a rotation component if the entity doesn't have non-rotatable component.
		// Optionally uses a scale.
		constexpr auto rotationQuery = PonyEngine::World::MakeQuery(
			PonyEngine::World::Required<Rotation, AngularVelocity>(),
			PonyEngine::World::Excluded<Nonrotatable>(),
			PonyEngine::World::Optional<Scale>());
		world->Query(rotationQuery.QueryParams, [&](const PonyEngine::World::QueryItem& item) noexcept
		{
			Rotation& rotation = rotationQuery.GetRequired<Rotation>(item);
			const AngularVelocity& angularVelocity = rotationQuery.GetRequired<AngularVelocity>(item);
			const Scale* const scale = rotationQuery.GetOptional<Scale>(item);
			PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Entity '{}' is rotating from '{}' by '{}'.",
				item.entity.id, rotation.value, angularVelocity.value);
			const PonyEngine::Math::Quaternion<float> scaledVelocity = scale
				? PonyEngine::Math::Quaternion<float>(angularVelocity.value.Vector() * scale->value)
				: angularVelocity.value;
			rotation.value *= scaledVelocity;
		});

		// Applies a linear velocity to an entity with a position component if the entity doesn't have immovable component.
		// Optionally uses a scale.
		constexpr auto movementQuery = PonyEngine::World::MakeQuery(
			PonyEngine::World::Required<Position, LinearVelocity>(),
			PonyEngine::World::Excluded<Immovable>(),
			PonyEngine::World::Optional<Scale>());
		world->Query(movementQuery.QueryParams, [&](const PonyEngine::World::QueryItem& item) noexcept
		{
			Position& position = movementQuery.GetRequired<Position>(item);
			const LinearVelocity& linearVelocity = movementQuery.GetRequired<LinearVelocity>(item);
			const Scale* const scale = rotationQuery.GetOptional<Scale>(item);
			PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Entity '{}' is moving from '{}' by '{}'.",
				item.entity.id, position.value, linearVelocity.value);
			const PonyEngine::Math::Vector3<float> scaledVelocity = scale
				? linearVelocity.value * scale->value
				: linearVelocity.value;
			position.value += scaledVelocity;
		});

		// Logs all the entities that have both a position and a rotation components.
		constexpr auto positionRotationQuery = PonyEngine::World::MakeQuery(
			PonyEngine::World::Required<Position, Rotation>());
		world->Query(positionRotationQuery.QueryParams, [&](const PonyEngine::World::QueryItem& item) noexcept
		{
			const Position& position = positionRotationQuery.GetRequired<Position>(item);
			const Rotation& rotation = positionRotationQuery.GetRequired<Rotation>(item);
			PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Entity '{}' has position '{}' and rotation '{}'.",
				item.entity.id, position.value, rotation.value);
		});

		// Logs all the objects that have a position component.
		// But it also optionally requests a rotation component. When it finds a rotation component, it terminates the query.
		constexpr auto positionStopOnRotationQuery = PonyEngine::World::MakeQuery(
			PonyEngine::World::Required<Position>(),
			PonyEngine::World::Optional<Rotation>());
		world->Query(positionStopOnRotationQuery.QueryParams, [&](PonyEngine::World::QueryItem& item) noexcept
		{
			const bool hasRotation = positionStopOnRotationQuery.GetOptional<Rotation>(item);
			PonyEngine::Log::LogToLogService(logService, PonyEngine::Log::LogType::Info, "Entity '{}' has rotation: '{}'.", item.entity.id, hasRotation);
			item.terminate = hasRotation;
		});
	}

	void GameModule::ShutDown(PonyEngine::Application::IModuleContext& context)
	{
	}
}
