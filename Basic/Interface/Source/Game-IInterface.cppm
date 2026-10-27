module;

#include "PonyEngine/Utility/Body.h"

export module Game:IInterface;

export namespace Game
{
	class IInterface // Example of an interface that is implemented.
	{
		PONY_INTERFACE_BODY(IInterface) // Adds default constructors, assignment operators and a destructor under a protected section and starts a public section.

		virtual void Run() = 0;
	};

	class IInvalidInterface // Example of an interface that is not implemented.
	{
		PONY_INTERFACE_BODY(IInvalidInterface)

		virtual void Run() = 0;
	};
}
