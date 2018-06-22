#pragma once
#include "MnRenderModuleSFML.h"
#include "SFML/Graphics.hpp"

namespace MNL
{
	//추가 확장을 위한 래퍼클래스
	class MnSprite : public MnRenderableSFML
	{
	public:
		MnSprite();
		~MnSprite();
		MnSprite(sf::Sprite sprite);
		MnSprite(const sf::Sprite& sprite);
		MnSprite(const sf::Texture& texture);
		MnSprite(const sf::Texture& texture, const sf::IntRect& rectangle);
	};
}