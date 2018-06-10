#pragma once
#include <memory>
#include <map>
#include "zip_utils\unzip.h"
#include "MnSingleton.h"

namespace MNL
{
	struct Resource
	{
		std::wstring _resourceName;
		long		 _bufSize;
		char*		 _memBuffer;
	};

	class ResourceManager : public MnSingleton<ResourceManager>
	{
	private:
		ResourceManager();
		~ResourceManager();

	public:
		bool						LoadResourcePackage(std::wstring packageFilePath);
		//returns null if resource is not exist
		const Resource*				GetResource(std::wstring keyName);
		//destroy resource and recover memory
		void						DestroyResource(std::wstring keyName);

	private:
		void						ClearResourceTable();

	private:
		std::map<std::wstring, Resource>	m_resourceTable;
	};

}