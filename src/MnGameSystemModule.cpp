#include "MnGameSystemModule.h"
#include "MnGameSystem.h"

MNL::MnGameSystemModule::MnGameSystemModule()
{
	_RegisterSelf();
}

MNL::MnGameSystemModule::~MnGameSystemModule()
{
	Release();
}

void MNL::MnGameSystemModule::Release()
{
	_UnregisterSelf();
}

void MNL::MnGameSystemModule::_RegisterSelf()
{
	auto pGameSystem = MnGameSystem::GetInstance();
	if (pGameSystem != nullptr)
	{
		pGameSystem->RegisterModule(this);
	}
}

void MNL::MnGameSystemModule::_UnregisterSelf()
{
	auto pGameSystem = MnGameSystem::GetInstance();
	if (pGameSystem != nullptr)
	{
		pGameSystem->UnregisterModule(this);
	}
}
