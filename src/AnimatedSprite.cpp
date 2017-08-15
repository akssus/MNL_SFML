#include "AnimatedSprite.h"
#include "ResourceManager.h"

using namespace MNL;

AnimatedSprite::AnimatedSprite():m_pCurrentFrame(nullptr)
{

}


AnimatedSprite::~AnimatedSprite()
{

}

/*
set animation sprite sheet from image file
@param imageFileName : sprite sheet file name in the pacakge or local path. png, bmp, etc.
*/
void AnimatedSprite::setSpriteSheet(std::wstring imageFileName)
{
	m_spriteSheet = SpriteManager::getInstance()->createSprite(imageFileName);
}

/*
read animation frame data from json
@param jsonFileName : json file name in the package or local path. it should contain string .json
*/
bool AnimatedSprite::setSheetData(std::wstring jsonFileName)
{
	AnimationFrameList* loadedFrames = SpriteManager::getInstance()->getFrameList(jsonFileName);
	if (loadedFrames == nullptr) return false; //json file doesn't exit
	m_lstFrames = *loadedFrames; //copy
	m_numFrames = m_lstFrames.size();
	setCurrentFrame(0);
	return true;
}
/*
set loop or not
*/
void AnimatedSprite::setLoop(bool isLoop)
{
	m_isLoop = isLoop;
}
/*
force to go to the index frame
@param index : frame index in the bound
*/
void AnimatedSprite::setCurrentFrame(int index)
{
	if (index >= 0 && index < m_numFrames)
	{
		m_pCurrentFrame = &m_lstFrames[index];
		m_spriteSheet.setTextureRect(m_pCurrentFrame->_rect);
	}
}
/*
go to the next frame of animation. no other operation.
if it is the last frame of the animation, then go to the start frame
*/
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
	m_extraTime = sf::Time();
}
/*
pause at current frame
*/
void AnimatedSprite::pause()
{
	if (m_isPlaying)
	{
		m_isPlaying = false;
	}
}
/*
resume playing animation
*/
void AnimatedSprite::play()
{
	m_isPlaying = true;
	m_loopMutex = true;
	m_clock.restart();
}

/*
rewind to start frame and play
*/
void AnimatedSprite::rewind()
{
	setCurrentFrame(0);
	play();
}

/*
check if it is last frame of animation
*/
bool AnimatedSprite::isAtLastFrame()
{
	return (m_pCurrentFrame->_index == m_numFrames - 1);
}
/*
check if the animation is playing
*/
bool AnimatedSprite::isPlaying()
{
	return m_isPlaying;
}

/*
animation status updates as time elapsed. 
if it is not looping, it paused at the last frame after it's duration.
so when resumed by using play(); starts at the start frame of anmation.
*/
void AnimatedSprite::update()
{
	if (m_pCurrentFrame == nullptr) return;

	if (m_isPlaying)
	{
		sf::Time duration = sf::milliseconds(m_pCurrentFrame->_duration);
	
		sf::Time elapsedTime = m_clock.getElapsedTime();
		m_extraTime += elapsedTime;

		while (m_extraTime.asMilliseconds() > duration.asMilliseconds())
		{
			if (isAtLastFrame() && !m_isLoop && !m_loopMutex)
			{
				pause();
				break;
			}
			else
			{
				gotoNextFrame();
				m_extraTime -= duration;
			} 
		}
	}
	m_loopMutex = false;
	m_clock.restart();
}

/*
render the animation sprite. 
this function contains update() function itself.
*/
void AnimatedSprite::render(sf::RenderWindow& window)
{
	if (m_pCurrentFrame == nullptr) return;
	update();
	window.draw(m_spriteSheet);
}