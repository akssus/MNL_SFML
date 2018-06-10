#pragma once

#include <map>
#include <list>
#include <string>
#include <memory>
#include "SFML/Audio.hpp"
#include "MnSingleton.h"

namespace MNL
{
	class SoundManager : public MnSingleton<SoundManager>
	{
	private:
		SoundManager();
		~SoundManager();

	public:

		void	PlaySFX(std::wstring sfxFileName);
		void	PlayMusic(std::wstring musicFileName);
		void	StopMusic();
		void	StopAllSFX();

		void	Update();

		bool	LoadSFXFromPackage(std::wstring sfxFileName);
		bool	LoadMusicFromPackage(std::wstring musicFileName);

	private:
		sf::SoundBuffer*	GetSoundBuffer(std::wstring sfxFileName);
		sf::Music*			GetMusic(std::wstring musicFileName);
	public:

	private:
		std::map<std::wstring, sf::SoundBuffer> m_soundBufferTable;
		std::map<std::wstring, std::shared_ptr<sf::Music> >		m_musicTable;
		std::list<std::shared_ptr<sf::Sound> >					m_soundQueue;
		sf::Music*								m_pCurrentMusic = nullptr;

	};
}