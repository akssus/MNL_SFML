#include "ResourceManager.h"

using namespace MNL;

ResourceManager* ResourceManager::m_pInstance = nullptr;

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	clearResourceTable();
}
ResourceManager* ResourceManager::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new ResourceManager();
	}
	return m_pInstance;
};

bool ResourceManager::loadResourcePackage(std::wstring packageFilePath)
{
	HZIP hZip = OpenZip(packageFilePath.c_str(), 0);
	if (hZip == nullptr) return false; //load file failed

	ZIPENTRY header;
	GetZipItem(hZip, -1, &header);
	int numitems = header.index;
	for (int entryIndex = 0; entryIndex < numitems; ++entryIndex)
	{
		ZIPENTRY ze;
		GetZipItem(hZip, entryIndex, &ze);
		Resource res;
		res._bufSize = ze.unc_size;
		res._memBuffer = new char[ze.unc_size];
		res._resourceName = ze.name;
		UnzipItem(hZip, entryIndex, res._memBuffer, ze.unc_size);
		m_resourceTable[res._resourceName] = res;
	}
	CloseZip(hZip);
	return true;
}

//returns null if resource is not exist
const Resource* ResourceManager::getResource(std::wstring keyName)
{
	return &m_resourceTable[keyName];
}

void ResourceManager::clearResourceTable()
{
	for (auto& resPair : m_resourceTable)
	{
		if (resPair.second._memBuffer != nullptr)
			delete resPair.second._memBuffer;
	}
	m_resourceTable.clear();
}