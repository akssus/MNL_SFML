#pragma once

namespace MNL
{
	class MnGameSystemModule
	{
	public:
		MnGameSystemModule();
		~MnGameSystemModule();

		void Release();

	private:
		void _RegisterSelf();
		void _UnregisterSelf();

	};
}