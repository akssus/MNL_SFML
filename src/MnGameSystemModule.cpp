#include "MnGameSystemModule.h"
#include "MnGameSystem.h"

MNL::MnGameSystemModule::MnGameSystemModule()
{
	
}

MNL::MnGameSystemModule::~MnGameSystemModule()
{
	_UnregisterSelf();
}

void MNL::MnGameSystemModule::_RegisterSelf()
{
	auto pGameSystem = MnGameSystem::GetInstance();
	if (pGameSystem != nullptr)
	{
		pGameSystem->RegisterModule(std::shared_ptr<MnGameSystemModule>(this));
	}
}

void MNL::MnGameSystemModule::_UnregisterSelf()
{
	auto pGameSystem = MnGameSystem::GetInstance();
	if (pGameSystem != nullptr)
	{
		pGameSystem->UnregisterModule(typeid(*this).name());
	}
}
