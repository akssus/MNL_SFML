#pragma once
#include <windows.h>
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
		static ResourceManager*		getInstance();
		void						freeInstance();

		bool						loadResourcePackage(std::wstring packageFilePath);
		//returns null if resource is not exist
		const Resource*				getResource(std::wstring keyName);
		//destroy resource and recover memory
		void						destroyResource(std::wstring keyName);

	private:
		void						clearResourceTable();

	private:
		static ResourceManager*				m_pInstance;
		std::map<std::wstring, Resource>	m_resourceTable;
	};

}