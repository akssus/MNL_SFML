#include "MnSprite.h"
using namespace MNL;
using namespace sf;

MnSprite::MnSprite()
{
	
}

MnSprite::~MnSprite()
{
}

MnSprite::MnSprite(sf::Sprite sprite) 
{
	m_spDrawable = std::static_pointer_cast<Drawable>(std::make_shared<sf::Sprite>(sprite));
}

MnSprite::MnSprite(const sf::Sprite& sprite) 
{
	m_spDrawable = std::static_pointer_cast<Drawable>(std::make_shared<sf::Sprite>(sprite));
}

MnSprite::MnSprite(const sf::Texture& texture) 
{
	m_spDrawable = std::static_pointer_cast<Drawable>(std::make_shared<sf::Sprite>(texture));
}

MnSprite::MnSprite(const sf::Texture& texture, const sf::IntRect& rectangle) 
{
	m_spDrawable = std::static_pointer_cast<Drawable>(std::make_shared<sf::Sprite>(texture, rectangle));
}
