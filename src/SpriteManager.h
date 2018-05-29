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
	private:
		SpriteManager();
		~SpriteManager();

	public:
		static SpriteManager*	GetInstance();
		sf::Sprite				CreateSprite(std::wstring imageFileName);
		sf::Texture*			GetTexture(std::wstring imageFileName);
		AnimationFrameList*		GetFrameList(std::wstring jsonFileName);

	private:
		void			FreeInstance();

		bool			LoadTextureFromLocalPath(std::wstring localFilePath);
		bool			LoadTextureFromPackage(std::wstring imageFileName);
		bool			LoadSheetDataFromJson(std::wstring jsonFileName);

	private:
		static SpriteManager* m_pInstance;
		std::map<std::wstring, std::shared_ptr<sf::Texture> > m_textureTable;
		std::map<std::wstring, AnimationFrameList> m_animationFrameListTable;

	};

}


#endif
