#pragma once
#include <memory>
#include <map>
#include "zip_utils\unzip.h"

namespace MNL
{
	struct Resource
	{
		std::wstring _resourceName;
		long		 _bufSize;
		char*		 _memBuffer;
	};

	class ResourceManager
	{
	private:
		ResourceManager();
		~ResourceManager();

	public:
		static ResourceManager*		GetInstance();
		void						FreeInstance();

		bool						LoadResourcePackage(std::wstring packageFilePath);
		//returns null if resource is not exist
		const Resource*				GetResource(std::wstring keyName);
		//destroy resource and recover memory
		void						DestroyResource(std::wstring keyName);

	private:
		void						ClearResourceTable();

	private:
		static ResourceManager*				m_pInstance;
		std::map<std::wstring, Resource>	m_resourceTable;
	};

}