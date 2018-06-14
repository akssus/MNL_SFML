#include "MnGameSystemModule.h"
#include "MnGameSystem.h"

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

MNL::MnGameSystemModule::MnGameSystemModule()
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
