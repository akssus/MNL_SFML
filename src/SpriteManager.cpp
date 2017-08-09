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

/*
load texture from resource manager and create sprite
@param		imageFileName : image file name in the package or local path
@return		copy of sf::sprite 
@error		returns empty sprite
*/
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

/*
load texture from resource manager
@param		imageFileName: image file name in the package or local path
@return		sf::Texture* in the texture table
@error		returns null
*/
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

AnimationFrameList* SpriteManager::getFrameList(std::wstring jsonFileName)
{
	if (m_animationFrameListTable.count(jsonFileName) == 0)
	{
		//if not in the table, try to load from packages
		bool loadJsonSucceed = loadSheetDataFromJson(jsonFileName);
		if (!loadJsonSucceed) return nullptr;
	}
	return &m_animationFrameListTable[jsonFileName];
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
		if (textureChunk == nullptr) return false;
		
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

bool SpriteManager::loadSheetDataFromJson(std::wstring jsonFileName)
{
	const Resource* jsonChunk = ResourceManager::getInstance()->getResource(jsonFileName);
	if (jsonChunk == nullptr) return false;

	std::istringstream jsonData(std::string(jsonChunk->_memBuffer, jsonChunk->_bufSize));
	nlohmann::json parsedData = nlohmann::json::parse(jsonData);

	AnimationFrameList lstFrames;
	int index = 0;
	for (auto& element : parsedData["frames"])
	{
		AnimationFrame frame;
		//parser does implicit conversion
		frame._index = index++;
		frame._duration = element["duration"];
		frame._duration /= 60.0f; //to per frames
		sf::IntRect rect;
		rect.left = element["frame"]["x"];
		rect.top = element["frame"]["y"];
		rect.width = element["frame"]["w"];
		rect.height = element["frame"]["h"];
		frame._rect = rect;
		lstFrames.push_back(frame);
	}
	if (lstFrames.size() == 0) return false; //json file corrupted

	m_animationFrameListTable[jsonFileName] = lstFrames;
	return true;
}