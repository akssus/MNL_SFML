#ifndef __SPRITE_MANAGER_H__
#define __SPRITE_MANAGER_H__
#include <map>
#include <memory>
#include <string>
#include "SFML/Graphics.hpp"


namespace MNL {

	class SpriteManager
	{
	public:
		~SpriteManager();
	private:
		SpriteManager();

	public:
		static SpriteManager* getInstance();
		sf::Sprite		createSprite(std::wstring imageFileName);

	private:
		void			freeInstance();
		sf::Texture*	getTexture(std::wstring imageFileName);
		bool			loadTextureFromLocalPath(std::wstring localFilePath);
		bool			loadTextureFromPackage(std::wstring imageFileName);

	private:
		static SpriteManager* m_pInstance;
		std::map<std::wstring, std::shared_ptr<sf::Texture> > m_textureTable;

	};

}


#endif
