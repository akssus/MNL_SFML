#include "MnSprite.h"
using namespace MNL;
using namespace sf;

MnSprite::MnSprite() : Sprite::Sprite()
{
	
}

MnSprite::MnSprite(sf::Sprite sprite) : Sprite::Sprite(sprite)
{
}

MnSprite::MnSprite(const sf::Sprite& sprite) : Sprite::Sprite(sprite)
{
}

MnSprite::MnSprite(const sf::Texture& texture) : Sprite::Sprite(texture)
{
}

MnSprite::MnSprite(const sf::Texture& texture, const sf::IntRect& rectangle) : Sprite::Sprite(texture, rectangle)
{
}
