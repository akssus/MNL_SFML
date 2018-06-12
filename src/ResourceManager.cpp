#include "ResourceManager.h"
#include "zip_utils/unzip.h"

using namespace MNL;


bool ResourceManager::LoadResourcePackage(std::wstring packageFilePath)
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

const Resource* ResourceManager::GetResource(std::wstring keyName)
{
	return (m_resourceTable.count(keyName) == 0) ? nullptr : &m_resourceTable[keyName];
}

void ResourceManager::ClearResourceTable()
{
	for (auto& resPair : m_resourceTable)
	{
		if (resPair.second._memBuffer != nullptr)
			delete resPair.second._memBuffer;
	}
	m_resourceTable.clear();
}

void ResourceManager::DestroyResource(std::wstring keyName)
{
	if (m_resourceTable.count(keyName) != 0)
	{
		if(m_resourceTable[keyName]._memBuffer != nullptr)
			delete m_resourceTable[keyName]._memBuffer;
		m_resourceTable.erase(keyName);
	}
}