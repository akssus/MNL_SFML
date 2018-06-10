#pragma once

#include <map>
#include <memory>
#include <string>
#include <strstream>
#include "SFML/Graphics.hpp"
#include "jsonnlohmann/json.hpp"
#include "MnSingleton.h"

namespace MNL {

	struct AnimationFrame
	{
		int			_index;
		int			_duration;
		sf::IntRect _rect;
	};
	typedef std::vector<MNL::AnimationFrame> AnimationFrameList;

	class SpriteManager : public MnSingleton<SpriteManager> 
	{
	private:
		SpriteManager();
		~SpriteManager();

	public:
		sf::Sprite				CreateSprite(std::wstring imageFileName);
		sf::Texture*			GetTexture(std::wstring imageFileName);
		AnimationFrameList*		GetFrameList(std::wstring jsonFileName);

	private:

		bool			LoadTextureFromLocalPath(std::wstring localFilePath);
		bool			LoadTextureFromPackage(std::wstring imageFileName);
		bool			LoadSheetDataFromJson(std::wstring jsonFileName);

	private:
		std::map<std::wstring, std::shared_ptr<sf::Texture> > m_textureTable;
		std::map<std::wstring, AnimationFrameList> m_animationFrameListTable;

	};

}