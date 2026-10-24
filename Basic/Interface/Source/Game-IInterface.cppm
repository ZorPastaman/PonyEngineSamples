module;

#include "PonyEngine/Utility/Body.h"

export module Game:IInterface;

export namespace Game
{
	class IInterface
	{
		PONY_INTERFACE_BODY(IInterface)

		virtual void Run() = 0;
	};

	class IInvalidInterface
	{
		PONY_INTERFACE_BODY(IInvalidInterface)

		virtual void Run() = 0;
	};
}
