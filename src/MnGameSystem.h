#pragma once
#include <memory>
#include <map>
#include "MnGameSystemModule.h"
#include "MnSingleton.h"
#include "MnBootstrap.h"
#include "MnIdentifierAllocator.h"
#include "MnMessageSystem.h"

#define MN_GAMESYSTEM_MODULE_ID_RANGE_FROM 0
#define MN_GAMESYSTEM_MODULE_ID_RANGE_TO 5000

namespace MNL
{
	class MnGameSystem : public MnSingleton<MnGameSystem>
	{
	public:
		MnGameSystem();
		~MnGameSystem();

		bool Boot();

		//������ moduleOrderMin �̻���� ã�� �Ҵ�.
		bool RegisterModule(std::shared_ptr<MnGameSystemModule> spModule, MnUINT32_ID moduleOrderMin = MN_GAMESYSTEM_MODULE_ID_RANGE_FROM);

		bool UnregisterModule(const std::string& moduleName);
		bool UnregisterModule(std::shared_ptr<MnGameSystemModule> spModule);

		template <typename T>
		bool UnregisterModule()
		{
			std::string moduleClassName = typeid(T).raw_name();
			return UnregisterModule(moduleClassName);
		}

		std::shared_ptr<MnGameSystemModule> GetModule(const std::string& moduleName);

		template <typename T>
		std::shared_ptr<T> GetModule()
		{
			std::string moduleClassName = typeid(T).raw_name();
			auto pModule = GetModule(moduleClassName);

			return pModule ? std::dynamic_pointer_cast<T>(pModule) : nullptr;
		}

		bool HasModule(const std::string& moduleName);

		template <typename T>
		bool HasModule()
		{
			std::string moduleClassName = typeid(T).raw_name();
			return HasModule(moduleClassName);
		}

		void Update();

		void DistributeMessage(const MnMessage* pMessage);

	protected:
		void _UpdateModules();
		void _FreeAllModules();
		void _SortModules();


	protected:
		std::shared_ptr<MnBootstrap> m_spBootstrap;
		std::map<std::string, MnUINT32_ID> m_lstModuleIDs;
		std::map <MnUINT32_ID, std::shared_ptr<MnGameSystemModule>,std::less<>> m_lstModules;
		MnMessageSystem m_messageSystem;

		MnIdentifierAllocator m_orderAllocator;

	};
}
