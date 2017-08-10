#pragma once

#include <map>
#include <list>
#include <string>
#include <memory>
#include "SFML/Audio.hpp"

namespace MNL
{
	class SoundManager
	{
	private:
		SoundManager();
		~SoundManager();

	public:
		static SoundManager*	getInstance();
		void					freeInstance();

		void	playSFX(std::wstring sfxFileName);
		void	playMusic(std::wstring musicFileName);
		void	stopMusic();
		void	stopAllSFX();

		void	update();

		bool				loadSFXFromPackage(std::wstring sfxFileName);
		bool				loadMusicFromPackage(std::wstring musicFileName);

	private:
		sf::SoundBuffer*	getSoundBuffer(std::wstring sfxFileName);
		sf::Music*			getMusic(std::wstring musicFileName);
	public:

	private:
		static SoundManager*					m_pInstance;
		std::map<std::wstring, sf::SoundBuffer> m_soundBufferTable;
		std::map<std::wstring, std::shared_ptr<sf::Music> >		m_musicTable;
		std::list<std::shared_ptr<sf::Sound> >					m_soundQueue;
		sf::Music*								m_pCurrentMusic = nullptr;

	};
}