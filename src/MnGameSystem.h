#pragma once
#include <vector>
#include <memory>
#include <map>
#include "MnGameSystemModule.h"
#include "MnSingleton.h"
#include "MnBootstrap.h"

namespace MNL
{
	class MnGameSystem : public MnSingleton<MnGameSystem>
	{
	public:
		MnGameSystem();
		~MnGameSystem();

		bool Boot();

		bool RegisterModule(std::shared_ptr<MnGameSystemModule> spModule);

		bool UnregisterModule(const std::string& moduleName);
		bool UnregisterModule(std::shared_ptr<MnGameSystemModule> spModule);

		template <typename T>
		bool UnregisterModule()
		{
			std::string moduleClassName = typeid(T).name();
			return UnregisterModule(moduleClassName);
		}

		std::shared_ptr<MnGameSystemModule> GetModule(const std::string& moduleName);

		template <typename T>
		std::shared_ptr<T> const * GetModule()
		{
			std::string moduleClassName = typeid(T).name();
			auto pModule = GetModule(moduleClassName);

			return pModule ? std::dynamic_pointer_cast<T>(pModule) : nullptr;
		}

		bool HasModule(const std::string& moduleName);

		template <typename T>
		bool HasModule()
		{
			std::string moduleClassName = typeid(T).name();
			return HasModule(moduleClassName);
		}

		void Update();

		void DistributeMessageToModules(const MnMessage* pMessage);

	protected:
		void _UpdateModules();
		void _FreeAllModules();
		void _SortModules();


	protected:
		std::shared_ptr<MnBootstrap> m_spBootstrap;
		std::map<std::string, std::shared_ptr<MnGameSystemModule> > m_lstModules;

	};
}
