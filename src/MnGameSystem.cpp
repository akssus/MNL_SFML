#include "MnGameSystem.h"
#include <algorithm>

using namespace MNL;

MnGameSystem::MnGameSystem()
{
	
}

MnGameSystem::~MnGameSystem()
{
	_FreeAllModules();
}

bool MnGameSystem::Boot()
{
	if(m_spBootstrap != nullptr)
	{
		m_spBootstrap->RegisterModules();

		return true;
	}
	return false;
}

bool MnGameSystem::RegisterModule(std::shared_ptr<MnGameSystemModule> spModule)
{
	if (spModule == nullptr) return false;

	const std::string moduleClassName = typeid(*spModule).name();
	m_lstModules[moduleClassName] = spModule;

	_SortModules();

	spModule->OnRegistered();

	return true;
}

bool MnGameSystem::UnregisterModule(const std::string & moduleName)
{
	auto it = m_lstModules.find(moduleName);
	if (it != m_lstModules.end())
	{
		it->second->OnUnregistering();

		m_lstModules.erase(it);
		return true;
	}
	return false;
}

bool MnGameSystem::UnregisterModule(std::shared_ptr<MnGameSystemModule> spModule)
{
	if (spModule == nullptr) return false;

	std::string moduleClassName = typeid(*spModule).name();
	return UnregisterModule(moduleClassName);
}

std::shared_ptr<MnGameSystemModule> MnGameSystem::GetModule(const std::string & moduleName)
{
	auto it = m_lstModules.find(moduleName);
	if (it != m_lstModules.end())
	{
		return it->second;
	}
	return std::shared_ptr<MnGameSystemModule>();
}

bool MnGameSystem::HasModule(const std::string & moduleName)
{
	auto pModule = GetModule(moduleName);
	return pModule != nullptr;
}

void MnGameSystem::Update()
{
	_UpdateModules();
}

void MnGameSystem::DistributeMessageToModules(const MnMessage* pMessage)
{
	for(auto& it : m_lstModules)
	{
		auto spModule = it.second;
		spModule->ReceiveMessage(pMessage);
	}
}

void MnGameSystem::_UpdateModules()
{
	for(auto& it : m_lstModules)
	{
		auto spModule = it.second;
		spModule->Update();
	}
}

void MnGameSystem::_FreeAllModules()
{
	auto it = m_lstModules.begin();
	while (it != m_lstModules.end())
	{
		//erase�� ���ͷ����� ���� ���� �� �־ ��Īó��
		it->second->OnUnregistering();
	}
	m_lstModules.clear();
}

void MnGameSystem::_SortModules()
{
	auto comp = [](std::pair<std::string, std::shared_ptr<MnGameSystemModule>>& keyA, std::pair<std::string, std::shared_ptr<MnGameSystemModule>>& keyB)
	{
		auto spModuleA = keyA.second;
		auto spModuleB = keyB.second;
		return spModuleA->GetModuleOrder() > spModuleB->GetModuleOrder();
	};
	std::sort(m_lstModules.begin(), m_lstModules.end(), comp);
}