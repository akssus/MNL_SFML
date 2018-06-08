#pragma once
#include <vector>
#include <memory>
#include <map>
#include "MnGameSystemModule.h"

namespace MNL
{
	class MnGameSystem
	{
	public:
		MnGameSystem();
		~MnGameSystem();


		void RegisterModule(const std::shared_ptr<MnGameSystemModule>& pModule)
		{
			if (pModule == nullptr) return;

			std::string moduleClassName = typeid(*pModule).name();
			_lstModules[moduleClassName] = pModule;
		}

		template <typename T>
		std::shared_ptr<T> GetModule()
		{
			std::string moduleClassName = typeid(T).name();
			
			auto it = _lstModules.find(moduleClassName);
			if(it != _lstModules.end())
			{
				return *it;
			}

			return nullptr;
		}


	private:


	private:
		std::map<std::string, std::shared_ptr<MnGameSystemModule>> _lstModules;


	};
}