#include "AnimatedSprite.h"
#include "ResourceManager.h"

using namespace MNL;

AnimatedSprite::AnimatedSprite():m_pCurrentFrame(nullptr)
{

}


AnimatedSprite::~AnimatedSprite()
{

}

void AnimatedSprite::SetSpriteSheet(std::wstring imageFileName)
{
	m_spriteSheet = SpriteManager::GetInstance()->CreateSprite(imageFileName);
}

bool AnimatedSprite::SetSheetData(std::wstring jsonFileName)
{
	AnimationFrameList* loadedFrames = SpriteManager::GetInstance()->GetFrameList(jsonFileName);
	if (loadedFrames == nullptr) return false; //json file doesn't exit
	m_lstFrames = *loadedFrames; //copy
	m_numFrames = m_lstFrames.size();
	SetCurrentFrame(0);
	return true;
}

void AnimatedSprite::SetLoop(bool isLoop)
{
	m_isLoop = isLoop;
}

void AnimatedSprite::SetCurrentFrame(int index)
{
	if (index >= 0 && index < m_numFrames)
	{
		m_pCurrentFrame = &m_lstFrames[index];
		m_spriteSheet.setTextureRect(m_pCurrentFrame->_rect);
	}
}

void AnimatedSprite::GotoNextFrame()
{
	int currentIndex = m_pCurrentFrame->_index;
	SetCurrentFrame((currentIndex + 1) % m_numFrames);
}

void AnimatedSprite::Stop()
{
	m_isPlaying = false;
	SetCurrentFrame(0);
	m_extraTime = sf::Time();
}

void AnimatedSprite::Pause()
{
	if (m_isPlaying)
	{
		m_isPlaying = false;
	}
}

void AnimatedSprite::Play()
{
	m_isPlaying = true;
	m_loopMutex = true;
	m_clock.restart();
}

void AnimatedSprite::Rewind()
{
	SetCurrentFrame(0);
	Play();
}

bool AnimatedSprite::IsAtLastFrame()
{
	return (m_pCurrentFrame->_index == m_numFrames - 1);
}

bool AnimatedSprite::IsPlaying()
{
	return m_isPlaying;
}


void AnimatedSprite::Update()
{
	if (m_pCurrentFrame == nullptr) return;

	if (m_isPlaying)
	{
		sf::Time duration = sf::milliseconds(m_pCurrentFrame->_duration);
	
		sf::Time elapsedTime = m_clock.getElapsedTime();
		m_extraTime += elapsedTime;

		while (m_extraTime.asMilliseconds() > duration.asMilliseconds())
		{
			if (IsAtLastFrame() && !m_isLoop && !m_loopMutex)
			{
				Pause();
				break;
			}
			else
			{
				GotoNextFrame();
				m_extraTime -= duration;
			} 
		}
	}
	m_loopMutex = false;
	m_clock.restart();
}

void AnimatedSprite::Render(sf::RenderWindow& window)
{
	if (m_pCurrentFrame == nullptr) return;
	Update();
	
	window.draw(m_spriteSheet);
}