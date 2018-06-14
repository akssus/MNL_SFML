#pragma once
#include "SFML/Graphics.hpp"

namespace MNL
{
	//�߰� Ȯ���� ���� ����Ŭ����
	class MnSprite : public sf::Sprite
	{
	public:
		MnSprite();
		MnSprite(sf::Sprite sprite);
		MnSprite(const sf::Sprite& sprite);
		MnSprite(const sf::Texture& texture);
		MnSprite(const sf::Texture& texture, const sf::IntRect& rectangle);
	};
}