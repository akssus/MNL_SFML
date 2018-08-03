#include "MnMessageSystem.h"
#include "MnGameSystem.h"
#include <algorithm>

using namespace MNL;

//---------------------------------------------
// 메시지
//---------------------------------------------

void MnMessage::Dispatch()
{
	MnGameSystem::GetInstance()->DistributeMessage(this);
}


//---------------------------------------------
// 메시지 리시버
//---------------------------------------------
MnMessageReceiver::MnMessageReceiver()
{
	
}

void MnMessageReceiver::ReceiveMessage(const MnMessage* pMessage)
{
	std::string key = typeid(*pMessage).raw_name();
	if (m_tblHandlers.find(key) != m_tblHandlers.end())
	{
		m_tblHandlers[key](pMessage);
	}
}

//---------------------------------------------
// 메시지 시스템
//---------------------------------------------

void MnMessageSystem::Register(const std::string& msgKey, const std::shared_ptr<MnMessageReceiver>& spMessageReceiver)
{
	if (spMessageReceiver != nullptr)
	{
		_AssureMessageBucket(msgKey);
		bool isRegistered = std::any_of(m_tblReceivers[msgKey].begin(), m_tblReceivers[msgKey].end(), [&](std::shared_ptr<MnMessageReceiver> receiver)
		{
			return receiver == spMessageReceiver;
		});
		if (!isRegistered)
		{
			m_tblReceivers[msgKey].push_back(spMessageReceiver);
		}
	}
}

void MnMessageSystem::Unregister(const std::shared_ptr<MnMessageReceiver>& spMessageReceiver)
{
	for(auto& tuple : m_tblReceivers)
	{
		auto& msgKey = tuple.first;
		Unregister(msgKey, spMessageReceiver);
	}
}

void MnMessageSystem::Unregister(const std::string& msgKey, const std::shared_ptr<MnMessageReceiver>& spMessageReceiver)
{
	if(m_tblReceivers.find(msgKey) != m_tblReceivers.end())
	{
		auto& receivers = m_tblReceivers[msgKey];
		auto it = std::find(receivers.begin(), receivers.end(), spMessageReceiver);
		if (it != receivers.end())
		{
			receivers.erase(it);
		}
	}
}

void MnMessageSystem::Distribute(const std::string& msgKey, const MnMessage* pMessage)
{
	std::for_each(m_tblReceivers[msgKey].begin(), m_tblReceivers[msgKey].end(), [&](std::shared_ptr<MnMessageReceiver>& receiver)
	{
		receiver->ReceiveMessage(pMessage);
	});
}


void MnMessageSystem::_AssureMessageBucket(const std::string& msgKey)
{
	if(m_tblReceivers.find(msgKey) == m_tblReceivers.end())
	{
		m_tblReceivers[msgKey] = std::vector<std::shared_ptr<MnMessageReceiver>>();
	}
}