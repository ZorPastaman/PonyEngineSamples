export module Game:GameTicker;

import std;

import PonyEngine.Application;
import PonyEngine.Memory;

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

		PonyEngine::Application::IApplication* application;
	};
}

namespace Game
{
	GameTicker::GameTicker(PonyEngine::Application::IApplication& application) noexcept :
		application{&application}
	{
	}

	PonyEngine::Application::ITickable& GameTicker::Tickable() noexcept
	{
		return *this;
	}

	void GameTicker::Tick()
	{
		constexpr std::size_t count = 31;

		constexpr std::size_t bufferSize = PonyEngine::Memory::CalculateBufferSize<std::uint32_t>(count) + // Calculates a buffer size for the first array.
			PonyEngine::Memory::CalculateBufferSize<std::uint64_t, std::uint32_t>(count); // Calculates a buffer size for the second array. The second type is a previous type. It's used to add a correct padding to allocates array with a correct alignment.
		const std::shared_ptr<PonyEngine::Application::IBuffer> buffer = application->CreateBuffer(bufferSize); // Creates a new buffer or gets a buffer from a pool if it has a suitable one.
		auto arena = PonyEngine::Memory::Arena(buffer->Span()); // Arena makes it easier to use the buffer.

		const std::span<std::uint32_t> smallInts = arena.AllocateArray<std::uint32_t>(count); // Allocates an array in the arena.
		const std::span<std::uint64_t> bigInts = arena.AllocateArray<std::uint64_t>(count); // These allocations must follow the same order and count that were used in buffer size calculation.

		for (std::size_t i = 0uz; i < count; ++i) // Use those spans in a usual manner.
		{
			smallInts[i] = static_cast<std::uint32_t>(i);
			bigInts[i] = static_cast<std::uint64_t>(i);
		}
	}
}
