#include "MnGameSystem.h"
#include <algorithm>
#include "MnDebugModule.h"

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
		m_spBootstrap->RegisterModules(*this);

		return true;
	}
	return false;
}

bool MnGameSystem::RegisterModule(std::shared_ptr<MnGameSystemModule> spModule, MnUINT32_ID moduleOrderMin)
{
	if (spModule == nullptr) return false;

	if(m_orderAllocator.IsFull())
	{
		MnDebug::WriteLog("더 이상 할당될 수 있는 모듈 자리가 없습니다", MN_LOGTYPE_ERROR);
		return false;
	}

	const std::string moduleClassName = typeid(*spModule).raw_name();

	auto allocatedOrder = m_orderAllocator.AllocateAbove(moduleOrderMin);
	spModule->SetModuleOrder(allocatedOrder);

	m_lstModuleIDs[moduleClassName] = allocatedOrder;
	m_lstModules[allocatedOrder] = spModule;

	_SortModules();

	spModule->OnRegistered();

	return true;
}

bool MnGameSystem::UnregisterModule(const std::string & moduleName)
{
	auto it = m_lstModuleIDs.find(moduleName);
	if (it != m_lstModuleIDs.end())
	{
		auto moduleID = it->second;
		m_lstModules[moduleID]->OnUnregistering();

		m_lstModules.erase(moduleID);
		m_lstModuleIDs.erase(moduleName);
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
	auto it = m_lstModuleIDs.find(moduleName);
	if (it != m_lstModuleIDs.end())
	{
		auto moduleID = it->second;
		return m_lstModules[moduleID];
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
	m_lstModuleIDs.clear();
}

void MnGameSystem::_SortModules()
{
	//이미 오름순으로 되어있어서 할필요없다
	//그리고 map을 sort하면 에러나더라 ㅅㅂ
}
