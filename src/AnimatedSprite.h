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

		void setSpriteSheet(std::wstring imageFileName);
		bool setSheetData(std::wstring jsonFileName);
		void setCurrentFrame(int index);
		void setLoop(bool isLoop);

		void gotoNextFrame();
		void stop();
		void pause();
		void play();
		void rewind();

		bool isAtLastFrame();
		bool isPlaying();

		void update();
		void render(sf::RenderWindow& window);
		
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