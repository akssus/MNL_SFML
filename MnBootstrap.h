#pragma once
#include <memory>
#include "src/MnGameSystem.h"

namespace MNL
{
	class MnBootstrap
	{
	public:
		MnBootstrap();
		~MnBootstrap();

		void RegisterModules();

	private:
		std::shared_ptr<MnGameSystem> m_spGameSystem;
	};
}