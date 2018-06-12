#include "SoundManager.h"
#include "ResourceManager.h"

using namespace MNL;


void SoundManager::PlaySFX(std::wstring sfxFileName)
{
	sf::SoundBuffer* pSoundBuffer = GetSoundBuffer(sfxFileName);
	if (pSoundBuffer == nullptr) return;

	sf::Sound* newSFX = new sf::Sound;
	newSFX->setBuffer(*pSoundBuffer);
	m_soundQueue.push_back(std::shared_ptr<sf::Sound>(newSFX));
	newSFX->play();
}
void SoundManager::PlayMusic(std::wstring musicFileName)
{
	sf::Music* pMusic = GetMusic(musicFileName);
	if (pMusic == nullptr) return;
	
	//stop already being played music
	if (m_pCurrentMusic != nullptr) m_pCurrentMusic->stop();
	m_pCurrentMusic = pMusic;
	m_pCurrentMusic->setLoop(true);
	m_pCurrentMusic->play();
}
void SoundManager::StopMusic()
{
	if (m_pCurrentMusic == nullptr) return;
	m_pCurrentMusic->stop();
}
void SoundManager::StopAllSFX()
{
	for (auto& pSound : m_soundQueue)
	{
		pSound->stop();
	}
	//it's ok. it is shared_ptr
	m_soundQueue.clear();
}
sf::SoundBuffer* SoundManager::GetSoundBuffer(std::wstring sfxFileName)
{
	if (m_soundBufferTable.count(sfxFileName) == 0)
	{
		bool loadSucceed = LoadSFXFromPackage(sfxFileName);
		if (!loadSucceed) return nullptr;
	}
	return &m_soundBufferTable[sfxFileName];
}

sf::Music* SoundManager::GetMusic(std::wstring musicFileName)
{
	if (m_musicTable.count(musicFileName) == 0)
	{
		bool loadSucceed = LoadMusicFromPackage(musicFileName);
		if (!loadSucceed) return nullptr;
	}
	return m_musicTable[musicFileName].get();
}
bool SoundManager::LoadSFXFromPackage(std::wstring sfxFileName)
{
	const Resource* soundChunk = ResourceManager::GetInstance()->GetResource(sfxFileName);
	if (soundChunk == nullptr) return false; //load sound failed

	sf::SoundBuffer soundBuffer;
	bool loadSucceed = soundBuffer.loadFromMemory(soundChunk->_memBuffer, soundChunk->_bufSize);
	if (!loadSucceed) return false;

	m_soundBufferTable[sfxFileName] = soundBuffer;
	return true;
}
bool SoundManager::LoadMusicFromPackage(std::wstring musicFileName)
{
	const Resource* soundChunk = ResourceManager::GetInstance()->GetResource(musicFileName);
	if (soundChunk == nullptr) return false; //load sound failed

	sf::Music* music = new sf::Music;;
	bool loadSucceed = music->openFromMemory(soundChunk->_memBuffer, soundChunk->_bufSize);
	if (!loadSucceed) return false;

	m_musicTable[musicFileName] = std::shared_ptr<sf::Music>(music);
	return true;
}


void SoundManager::Update()
{
	//remove already played sfx
	auto& it = std::remove_if(m_soundQueue.begin(),m_soundQueue.end(),[](std::shared_ptr<sf::Sound> pSound){
		if (pSound->getStatus() == sf::Sound::Stopped) return true;
		return false;
	});
	m_soundQueue.erase(it, m_soundQueue.end());
}