#include "ParticleManager.h"

using namespace MNL;

ParticleManager* ParticleManager::m_pInstance = nullptr;

ParticleManager::ParticleManager()
{
}


ParticleManager::~ParticleManager()
{

}


ParticleManager* ParticleManager::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new ParticleManager;
	}
	return m_pInstance;
}

void ParticleManager::freeInstance()
{
	if (m_pInstance != nullptr)
		delete m_pInstance;
	m_pInstance = nullptr;
}
ParticleSystem	ParticleManager::createParticleSystem(ParticleDescription& desc)
{
	ParticleSystem ps;
	ps.initSystem(desc);
	return ps;
}
/*
ParticleSystem	ParticleManager::createParticleSystem(std::wstring jsonFileName)
{
	//implement later
}
*/
void ParticleManager::spreadParticleSystem(ParticleSystem& ps)
{
	m_particleSystemQueue.push_back(ps);
}
void ParticleManager::createAndSpreadParticleSystem(ParticleDescription& desc)
{
	m_particleSystemQueue.push_back(createParticleSystem(desc));
}
void ParticleManager::createAndSpreadParticleSystem(std::wstring jsonFileName)
{
	//m_particleSystemQueue.push_back(createParticleSystem(jsonFileName));
}


void ParticleManager::clearParticleSystems()
{
	m_particleSystemQueue.clear();
}
void ParticleManager::update()
{
	for (auto& particleSystem : m_particleSystemQueue)
	{
		particleSystem.update();
	}
	//remove finished particle system
	std::remove_if(m_particleSystemQueue.begin(), m_particleSystemQueue.end(), 
		[](ParticleSystem& ps) { 
			if (!ps.m_isAlive) return true; 
			return false;
		}
	);
}
void ParticleManager::render(sf::RenderWindow& window)
{
	for (auto& particleSystem : m_particleSystemQueue)
	{
		particleSystem.render(window);
	}
}
