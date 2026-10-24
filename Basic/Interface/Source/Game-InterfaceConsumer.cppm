export module Game:InterfaceConsumer;

import std;

import PonyEngine.Application;

import :IInterface;

export namespace Game
{
	class InterfaceConsumer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit InterfaceConsumer(PonyEngine::Application::IApplication& application);
		InterfaceConsumer(const InterfaceConsumer&) = delete;
		InterfaceConsumer(InterfaceConsumer&&) = delete;

		~InterfaceConsumer() noexcept;

		InterfaceConsumer& operator =(const InterfaceConsumer&) = delete;
		InterfaceConsumer& operator =(InterfaceConsumer&&) = delete;

	private:
		IInterface* interface;
		IInvalidInterface* invalidInterface;
	};
}

namespace Game
{
	InterfaceConsumer::InterfaceConsumer(PonyEngine::Application::IApplication& application) :
		interface{&application.GetInterface<IInterface>()},
		invalidInterface{application.FindInterface<IInvalidInterface>()}
	{
		// Add start-up logic here.

		interface->Run();

		if (invalidInterface)
		{
			invalidInterface->Run();
		}
	}

	InterfaceConsumer::~InterfaceConsumer() noexcept
	{
		// Add shut-down logic here.
	}
}
