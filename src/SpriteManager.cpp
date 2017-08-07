#include "SpriteManager.h"
#include "ResourceManager.h"
#include <codecvt>

using namespace MNL;

SpriteManager* SpriteManager::m_pInstance = nullptr;

SpriteManager::SpriteManager()
{

}
SpriteManager::~SpriteManager()
{
	freeInstance();
}
SpriteManager* SpriteManager::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new SpriteManager();
	}
	return m_pInstance;
};

void SpriteManager::freeInstance()
{
	m_textureTable.clear();

	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
	}
	m_pInstance = nullptr;
}

sf::Sprite SpriteManager::createSprite(std::wstring imageFileName)
{
	sf::Sprite		newSprite;
	sf::Texture*	newTexture;
	
	newTexture = getTexture(imageFileName);
	if(newTexture != nullptr)
	{
		newSprite.setTexture(*newTexture);
	}
	return newSprite;
}

sf::Texture* SpriteManager::getTexture(std::wstring imageFileName)
{
	sf::Texture* newTexture = nullptr;
	bool textureLoadSuccess = true;

	//find image from table
	if (m_textureTable.count(imageFileName) == 0)
	{
		//if not exist then try to load from memory
		if (loadTextureFromPackage(imageFileName) == false)
		{
			if (loadTextureFromLocalPath(TCHAR("res/") + imageFileName) == false)
			{
				//load failed
				textureLoadSuccess = false;
			}
		}
	}
	if(textureLoadSuccess) newTexture = m_textureTable[imageFileName].get();

	return newTexture;
}
bool SpriteManager::loadTextureFromLocalPath(std::wstring localFilePath)
{
	//insert only if it doesnt exist
	if (m_textureTable.count(localFilePath) == 0)
	{
		sf::Texture* newTexture = new sf::Texture();
		std::string str_path = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(localFilePath);
		bool textureLoadSuccess = newTexture->loadFromFile(str_path);
		if (!textureLoadSuccess)
		{
			delete newTexture;
			newTexture = nullptr;
			//or return as default texture
		}
	}
	return true;
}

bool SpriteManager::loadTextureFromPackage(std::wstring imageFileName)
{
	//insert only if it doesnt exist
	if (m_textureTable.count(imageFileName) == 0)
	{
		sf::Texture* newTexture = new sf::Texture();
		ResourceManager* pResourceManager = ResourceManager::getInstance();
		const Resource* textureChunk = pResourceManager->getResource(imageFileName);
		
		bool textureLoadSuccess = newTexture->loadFromMemory(textureChunk->_memBuffer, textureChunk->_bufSize);
		if (!textureLoadSuccess)
		{
			delete newTexture;
			return false;
		}
		m_textureTable[imageFileName] = std::shared_ptr<sf::Texture>(newTexture);

	}
	return true;
}