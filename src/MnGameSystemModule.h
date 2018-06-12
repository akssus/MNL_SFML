#pragma once
#include <wingdi.h>

namespace MNL
{
	class MnGameSystemModule
	{
	public:
		MnGameSystemModule();
		virtual ~MnGameSystemModule();

		virtual void OnRegistered() = 0;
		virtual void OnUnregistering() = 0;
		virtual void Update() = 0;

	private:
		[[deprecated]] void _RegisterSelf();
		void _UnregisterSelf();

	};
}
