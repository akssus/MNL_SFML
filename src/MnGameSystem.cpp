#include "MnGameSystem.h"

using namespace MNL;

MNL::MnGameSystem::MnGameSystem()
{
}

MNL::MnGameSystem::~MnGameSystem()
{
	_FreeAllModules();
}

bool MNL::MnGameSystem::RegisterModule(const MnGameSystemModule* pModule)
{
	if (pModule == nullptr) return false;

	std::string moduleClassName = typeid(*pModule).name();
	_lstModules[moduleClassName] = const_cast<MnGameSystemModule*>(pModule);

	return true;
}

bool MNL::MnGameSystem::UnreigsterModule(const std::string & moduleName)
{
	auto it = _lstModules.find(moduleName);
	if (it != _lstModules.end())
	{
		_lstModules.erase(it);
		return true;
	}
	return false;
}

bool MNL::MnGameSystem::UnregisterModule(const MnGameSystemModule * pModule)
{
	if (pModule == nullptr) return false;

	std::string moduleClassName = typeid(*pModule).name();
	return UnregisterModule(moduleClassName);
}

MnGameSystemModule* const MNL::MnGameSystem::GetModule(const std::string & moduleName)
{
	auto it = _lstModules.find(moduleName);
	if (it != _lstModules.end())
	{
		return it->second;
	}
	return nullptr;
}

bool MNL::MnGameSystem::HasModule(const std::string & moduleName)
{
	auto pModule = GetModule(moduleName);
	return pModule != nullptr;
}

void MNL::MnGameSystem::_FreeAllModules()
{
	auto it = _lstModules.begin();
	while (it != _lstModules.end())
	{
		auto pModule = it->second;
		pModule->Release();
		delete pModule;
	}
}
