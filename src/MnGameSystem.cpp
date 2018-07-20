#include "MnGameSystem.h"
#include <algorithm>

using namespace MNL;

MnGameSystem::MnGameSystem() : m_orderAllocator(MN_GAMESYSTEM_MODULE_ID_RANGE_FROM, MN_GAMESYSTEM_MODULE_ID_RANGE_TO)
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

bool MnGameSystem::RegisterModule(std::shared_ptr<MnGameSystemModule> spModule, MnUINT32_ID moduleOrderMin)
{
	if (spModule == nullptr) return false;

	if(m_orderAllocator.IsFull())
	{
		//DebugLogger.Print("더이상 할당될 수 있는 모듈 자리가 없습니다")
		return false;
	}

	const std::string moduleClassName = typeid(*spModule).raw_name();
	m_lstModules[moduleClassName] = spModule;

	auto allocatedOrder = m_orderAllocator.AllocateAbove(moduleOrderMin);
	spModule->SetModuleOrder(allocatedOrder);

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

	std::string moduleClassName = typeid(*spModule).raw_name();
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

void MnGameSystem::DistributeMessage(const MnMessage* pMessage)
{
	auto msgKey = typeid(*pMessage).raw_name();
	m_messageSystem.Distribute(msgKey, pMessage);
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
		//erase로 이터레이팅 문제 터질 수 있어서 배칭처리
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
