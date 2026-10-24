export module Game:InterfaceConsumerModule;

import std;

import PonyEngine.Application;

import :InterfaceConsumer;

export namespace Game
{
	class InterfaceConsumerModule final : public PonyEngine::Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		InterfaceConsumerModule() noexcept = default;
		InterfaceConsumerModule(const InterfaceConsumerModule&) = delete;
		InterfaceConsumerModule(InterfaceConsumerModule&&) = delete;

		~InterfaceConsumerModule() noexcept = default;

		virtual void StartUp(PonyEngine::Application::IModuleContext& context) override;
		virtual void ShutDown(PonyEngine::Application::IModuleContext& context) override;

		InterfaceConsumerModule& operator =(const InterfaceConsumerModule&) = delete;
		InterfaceConsumerModule& operator =(InterfaceConsumerModule&&) = delete;

	private:
		std::unique_ptr<InterfaceConsumer> consumer;
	};
}

namespace Game
{
	void InterfaceConsumerModule::StartUp(PonyEngine::Application::IModuleContext& context)
	{
		consumer = std::make_unique<InterfaceConsumer>(context.Application());
	}

	void InterfaceConsumerModule::ShutDown(PonyEngine::Application::IModuleContext& context)
	{
		consumer.reset();
	}
}
