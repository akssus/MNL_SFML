#pragma once

#include <vector>
#include <string>
#include "SFML/Graphics.hpp"
#include "SpriteManager.h"

namespace MNL
{
	//extern struct AnimationFrame;
	//typedef std::vector<AnimationFrame> AnimationFrameList;

	class AnimatedSprite
	{
	public:
		AnimatedSprite();
		~AnimatedSprite();

		void SetSpriteSheet(std::wstring imageFileName);
		bool SetSheetData(std::wstring jsonFileName);
		void SetCurrentFrame(int index);
		void SetLoop(bool isLoop);

		void GotoNextFrame();
		void Stop();
		void Pause();
		void Play();
		void Rewind();

		bool IsAtLastFrame();
		bool IsPlaying();

		void Update();
		void Render(sf::RenderWindow& window);
		
	private:
		sf::Clock						m_clock;
		sf::Time						m_extraTime;
		AnimationFrameList				m_lstFrames;
		int								m_numFrames			= 0;
		AnimationFrame*					m_pCurrentFrame		= nullptr;
		sf::Sprite						m_spriteSheet;
		int								m_frameCounter		= 0;
		bool							m_isPlaying			= true;
		bool							m_isLoop			= true;
		bool							m_loopMutex			= false;
	};
}