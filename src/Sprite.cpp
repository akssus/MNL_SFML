#include "Sprite.h"
using namespace MNL::GOComponents;


void Sprite::SetImage(std::shared_ptr<MnSprite> spImage)
{
	if(spImage != nullptr)
	{
		m_spSprite = spImage;
	}
}

std::shared_ptr<MNL::MnSprite> Sprite::GetImage()
{
	return m_spSprite;
}
