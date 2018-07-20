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

		//�������̵� �ؼ� �����սô�
		virtual void RegisterModules() = 0;

	protected:
		std::shared_ptr<MnGameSystem> m_spGameSystem;
	};
}
