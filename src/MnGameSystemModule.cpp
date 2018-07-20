#include "MnGameSystemModule.h"
#include "MnGameSystem.h"
#include <algorithm>

using namespace MNL;

MnGameSystemModule::MnGameSystemModule() : m_moduleOrder(5000)
{
	m_spMessageReceiver = std::make_shared<MnMessageReceiver>();
}

MnGameSystemModule::~MnGameSystemModule()
{
	_UnregisterSelf();
}

std::shared_ptr<MnMessageReceiver> MnGameSystemModule::GetMessageReceiver()
{
	return m_spMessageReceiver;
}

void MnGameSystemModule::SetModuleOrder(int32_t order)
{
	order = std::max(order, 0);
	m_moduleOrder = order;
}

int32_t MnGameSystemModule::GetModuleOrder()
{
	return m_moduleOrder;
}

void MnGameSystemModule::_RegisterSelf()
{
	auto pGameSystem = MnGameSystem::GetInstance();
	if (pGameSystem != nullptr)
	{
		pGameSystem->RegisterModule(std::shared_ptr<MnGameSystemModule>(this));
	}
}

void MnGameSystemModule::_UnregisterSelf()
{
	auto pGameSystem = MnGameSystem::GetInstance();
	if (pGameSystem != nullptr)
	{
		pGameSystem->UnregisterModule(typeid(*this).raw_name());
	}
}
