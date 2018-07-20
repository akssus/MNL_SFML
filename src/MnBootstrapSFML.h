#pragma once
#include "MnBootstrap.h"

#define MN_MODULE_ORDER_PLATFORM 500
#define MN_MODULE_ORDER_PRE_PROCESS 1000
#define MN_MODULE_ORDER_CORE 2000
#define MN_MODULE_ORDER_UTILITY 3000
#define MN_MODULE_ORDER_POST_PROCESS 4000

namespace MNL
{
	class MnBootstrapSFML : public MnBootstrap
	{
	public:
		void RegisterModules() override;
	};
}