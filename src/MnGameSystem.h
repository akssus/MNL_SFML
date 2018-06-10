#pragma once
#include <vector>
#include <memory>
#include <map>
#include "MnGameSystemModule.h"
#include "MnSingleton.h"

namespace MNL
{
	class MnGameSystem : public MnSingleton<MnGameSystem>
	{
	public:
		MnGameSystem();
		~MnGameSystem();

		bool RegisterModule(const MnGameSystemModule* pModule);
		bool UnreigsterModule(const std::string& moduleName);
		bool UnregisterModule(const MnGameSystemModule* pModule);

		template <typename T>
		bool UnregisterModule()
		{
			std::string moduleClassName = typeid(T).name();
			return UnregisterModule(moduleClassName);
		}

		MnGameSystemModule* const GetModule(const std::string& moduleName);

		template <typename T>
		T const * GetModule()
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


	private:
		void _FreeAllModules();

	private:
		std::map<std::string, MnGameSystemModule* > _lstModules;

	};
}