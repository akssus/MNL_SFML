#ifndef __SPRITE_MANAGER_H__
#define __SPRITE_MANAGER_H__
#include <map>
#include <memory>
#include <string>
#include <strstream>
#include "SFML/Graphics.hpp"
#include "jsonnlohmann/json.hpp"

namespace MNL {

	struct AnimationFrame
	{
		int			_index;
		int			_duration;
		sf::IntRect _rect;
	};
	typedef std::vector<MNL::AnimationFrame> AnimationFrameList;


	class SpriteManager
	{
	public:
		~SpriteManager();
	private:
		SpriteManager();

	public:
		static SpriteManager*	getInstance();
		sf::Sprite				createSprite(std::wstring imageFileName);
		AnimationFrameList*		getFrameList(std::wstring jsonFileName);

	private:
		void			freeInstance();
		sf::Texture*	getTexture(std::wstring imageFileName);

		bool			loadTextureFromLocalPath(std::wstring localFilePath);
		bool			loadTextureFromPackage(std::wstring imageFileName);
		bool			loadSheetDataFromJson(std::wstring jsonFileName);

	private:
		static SpriteManager* m_pInstance;
		std::map<std::wstring, std::shared_ptr<sf::Texture> > m_textureTable;
		std::map<std::wstring, AnimationFrameList> m_animationFrameListTable;

	};

}


#endif
