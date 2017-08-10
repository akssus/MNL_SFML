#include "AnimatedSprite.h"
#include "ResourceManager.h"

using namespace MNL;

AnimatedSprite::AnimatedSprite()
{

}


AnimatedSprite::~AnimatedSprite()
{

}

void AnimatedSprite::setSpriteSheet(std::wstring imageFileName)
{
	m_spriteSheet = SpriteManager::getInstance()->createSprite(imageFileName);
}

bool AnimatedSprite::setSheetData(std::wstring jsonFileName)
{
	AnimationFrameList* loadedFrames = SpriteManager::getInstance()->getFrameList(jsonFileName);
	if (loadedFrames == nullptr) return false; //json file doesn't exit
	m_lstFrames = *loadedFrames; //copy
	m_numFrames = m_lstFrames.size();
	setCurrentFrame(0);
	return true;
}

void AnimatedSprite::setCurrentFrame(int index)
{
	if (index >= 0 && index < m_numFrames)
	{
		m_pCurrentFrame = &m_lstFrames[index];
		m_spriteSheet.setTextureRect(m_pCurrentFrame->_rect);
	}
}
void AnimatedSprite::gotoNextFrame()
{
	int currentIndex = m_pCurrentFrame->_index;
	setCurrentFrame((currentIndex + 1) % m_numFrames);
}
/*
stop animation and return to 0 frame
*/
void AnimatedSprite::stop()
{
	m_isPlaying = false;
	setCurrentFrame(0);
}
/*
pause at current frame
*/
void AnimatedSprite::pause()
{
	m_isPlaying = false;
}
/*
resume playing animation
*/
void AnimatedSprite::play()
{
	m_isPlaying = true;
}

void AnimatedSprite::update()
{
	if (m_pCurrentFrame == nullptr) return;
	if (m_isPlaying)
	{
		m_frameCounter++;
		if (m_frameCounter > m_pCurrentFrame->_duration)
		{
			gotoNextFrame();
			m_frameCounter = 0;
		}
	}
}

void AnimatedSprite::render(sf::RenderWindow& window)
{
	if (m_pCurrentFrame == nullptr) return;
	update();
	window.draw(m_spriteSheet);
}