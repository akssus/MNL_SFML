#pragma once
#include "MnInputModule.h"


namespace MNL
{
	class MnInputModuleSFML : public MnInputModule
	{
	public:
		MnKeyState GetKeyState(const std::string& keyName) override;
	};
}
