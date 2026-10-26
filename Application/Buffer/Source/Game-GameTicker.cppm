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
		constexpr std::size_t count = 32;

		constexpr std::size_t bufferSize = PonyEngine::Memory::CalculateBufferSize<std::uint32_t>(count) + 
			PonyEngine::Memory::CalculateBufferSize<std::uint64_t, std::uint32_t>(count);
		const std::shared_ptr<PonyEngine::Application::IBuffer> buffer = application->CreateBuffer(bufferSize);
		auto arena = PonyEngine::Memory::Arena(buffer->Span());

		const std::span<std::uint32_t> smallInts = arena.AllocateArray<std::uint32_t>(count);
		const std::span<std::uint64_t> bigInts = arena.AllocateArray<std::uint64_t>(count);

		for (std::size_t i = 0uz; i < count; ++i)
		{
			smallInts[i] = static_cast<std::uint32_t>(i);
			bigInts[i] = static_cast<std::uint64_t>(i);
		}
	}
}
