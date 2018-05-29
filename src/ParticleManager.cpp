#include "ParticleManager.h"

using namespace MNL;

ParticleManager* ParticleManager::m_pInstance = nullptr;

ParticleManager::ParticleManager() = default;


ParticleManager::~ParticleManager() = default;


ParticleManager* ParticleManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new ParticleManager;
	}
	return m_pInstance;
}

void ParticleManager::FreeInstance()
{
	if (m_pInstance != nullptr)
		delete m_pInstance;
	m_pInstance = nullptr;
}
ParticleSystem	ParticleManager::CreateParticleSystem(ParticleDescription& desc)
{
	ParticleSystem ps;
	ps.InitSystem(desc);
	return ps;
}

ParticleSystem	ParticleManager::CreateParticleSystem(const std::wstring& jsonFileName)
{
	//implement later
}

void ParticleManager::SpreadParticleSystem(ParticleSystem& ps)
{
	m_particleSystemQueue.push_back(ps);
}
void ParticleManager::CreateAndSpreadParticleSystem(ParticleDescription& desc)
{
	m_particleSystemQueue.push_back(CreateParticleSystem(desc));
}
void ParticleManager::CreateAndSpreadParticleSystem(const std::wstring& jsonFileName)
{
	m_particleSystemQueue.push_back(CreateParticleSystem(jsonFileName));
}


void ParticleManager::ClearParticleSystems()
{
	m_particleSystemQueue.clear();
}
void ParticleManager::Update()
{
	for (auto& particleSystem : m_particleSystemQueue)
	{
		particleSystem.Update();
	}
	//remove finished particle system
	auto& it = std::remove_if(m_particleSystemQueue.begin(), m_particleSystemQueue.end(), 
		[](ParticleSystem& ps) { 
			if (!ps.m_isAlive) return true; 
			return false;
		}
	);
	m_particleSystemQueue.erase(it, m_particleSystemQueue.end());
}
void ParticleManager::Render(sf::RenderWindow& window)
{
	for (auto& particleSystem : m_particleSystemQueue)
	{
		particleSystem.Render(window);
	}
}
