#include "MnGameSystemModule.h"
#include "MnGameSystem.h"
#include <algorithm>

void MNL::MnMessage::Dispatch()
{
	MnGameSystem::GetInstance()->DistributeMessageToModules(this);
}

void MNL::MnMessageReceiver::ReceiveMessage(const MnMessage* pMessage)
{
	std::string key = typeid(*pMessage).name();
	if (m_tblHandlers.find(key) != m_tblHandlers.end())
	{
		m_tblHandlers[key](pMessage);
	}
}

MNL::MnGameSystemModule::MnGameSystemModule() : m_moduleOrder(5000)
{
	
}

MNL::MnGameSystemModule::~MnGameSystemModule()
{
	_UnregisterSelf();
}

void MNL::MnGameSystemModule::ReceiveMessage(const MnMessage* pMessage)
{
	m_messageReceiver.ReceiveMessage(pMessage);
}

void MNL::MnGameSystemModule::SetModuleOrder(int32_t order)
{
	order = std::max(order, 0);
	m_moduleOrder = order;
}

int32_t MNL::MnGameSystemModule::GetModuleOrder()
{
	return m_moduleOrder;
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
