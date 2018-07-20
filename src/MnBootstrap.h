#pragma once
#include <memory>
#include "MnGameSystem.h"

namespace MNL
{
	class MnBootstrap
	{
	public:
		MnBootstrap();
		virtual ~MnBootstrap();

		//오버라이드 해서 조립합시다
		virtual void RegisterModules() = 0;

	protected:
		std::shared_ptr<MnGameSystem> m_spGameSystem;
	};
}
