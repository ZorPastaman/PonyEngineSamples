export module Game:InterfaceProvider;

import std;

import PonyEngine.Application;

import :IInterface;

export namespace Game
{
	class InterfaceProvider final : public IInterface
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit InterfaceProvider(PonyEngine::Application::IApplication& application) noexcept;
		InterfaceProvider(const InterfaceProvider&) = delete;
		InterfaceProvider(InterfaceProvider&&) = delete;

		~InterfaceProvider() noexcept;

		virtual void Run() override;

		InterfaceProvider& operator =(const InterfaceProvider&) = delete;
		InterfaceProvider& operator =(InterfaceProvider&&) = delete;
	};
}

namespace Game
{
	InterfaceProvider::InterfaceProvider(PonyEngine::Application::IApplication& application) noexcept
	{
		// Add start-up logic here.
	}

	InterfaceProvider::~InterfaceProvider() noexcept
	{
		// Add shut-down logic here.
	}

	void InterfaceProvider::Run()
	{
		// Interface function implementation.
	}
}
