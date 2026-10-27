export module Game:InterfaceProviderModule;

import std;

import PonyEngine.Application;

import :InterfaceProvider;

export namespace Game
{
	class InterfaceProviderModule final : public PonyEngine::Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		InterfaceProviderModule() noexcept = default;
		InterfaceProviderModule(const InterfaceProviderModule&) = delete;
		InterfaceProviderModule(InterfaceProviderModule&&) = delete;

		~InterfaceProviderModule() noexcept = default;

		virtual void StartUp(PonyEngine::Application::IModuleContext& context) override;
		virtual void ShutDown(PonyEngine::Application::IModuleContext& context) override;

		InterfaceProviderModule& operator =(const InterfaceProviderModule&) = delete;
		InterfaceProviderModule& operator =(InterfaceProviderModule&&) = delete;

	private:
		std::unique_ptr<InterfaceProvider> provider;
	};
}

namespace Game
{
	void InterfaceProviderModule::StartUp(PonyEngine::Application::IModuleContext& context)
	{
		provider = std::make_unique<InterfaceProvider>(context.Application()); // Creates a provider.
		context.AddInterface<IInterface>(*provider); // Adds the interface to the application.
	}

	void InterfaceProviderModule::ShutDown(PonyEngine::Application::IModuleContext& context)
	{
		context.RemoveInterface<IInterface>(*provider); // Removes the interface from the application.
		provider.reset(); // Now it's safe to destroy the provider.
	}
}
