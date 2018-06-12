#include "MnGameSystem.h"

using namespace MNL;

MNL::MnGameSystem::MnGameSystem()
{
}

MNL::MnGameSystem::~MnGameSystem()
{
	_FreeAllModules();
}

bool MNL::MnGameSystem::RegisterModule(std::shared_ptr<MnGameSystemModule> spModule)
{
	if (spModule == nullptr) return false;

	const std::string moduleClassName = typeid(*spModule).name();
	m_lstModules[moduleClassName] = spModule;

	spModule->OnRegistered();

	return true;
}

bool MNL::MnGameSystem::UnregisterModule(const std::string & moduleName)
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

bool MNL::MnGameSystem::UnregisterModule(std::shared_ptr<MnGameSystemModule> spModule)
{
	if (spModule == nullptr) return false;

	std::string moduleClassName = typeid(*spModule).name();
	return UnregisterModule(moduleClassName);
}

std::shared_ptr<MnGameSystemModule> MNL::MnGameSystem::GetModule(const std::string & moduleName)
{
	auto it = m_lstModules.find(moduleName);
	if (it != m_lstModules.end())
	{
		return it->second;
	}
	return std::shared_ptr<MnGameSystemModule>();
}

bool MNL::MnGameSystem::HasModule(const std::string & moduleName)
{
	auto pModule = GetModule(moduleName);
	return pModule != nullptr;
}

void MNL::MnGameSystem::_FreeAllModules()
{
	auto it = m_lstModules.begin();
	while (it != m_lstModules.end())
	{
		//erase로 이터레이팅 문제 터질 수 있어서 배칭처리
		it->second->OnUnregistering();
	}
	m_lstModules.clear();
}
