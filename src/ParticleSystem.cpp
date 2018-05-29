#include "ParticleSystem.h"
#include "Thor/Vectors.hpp"
#include "Thor/Math.hpp"
#include "Thor/Math/Random.hpp"
#include "SpriteManager.h"


using namespace MNL;

ParticleSystem::ParticleSystem() = default;

ParticleSystem::~ParticleSystem()
{
	m_particleQueue.clear();
}
void ParticleSystem::InitSystem(ParticleDescription& desc)
{
	m_particleDescription = desc;
	m_systemDuration = desc._systemDuration;
	m_fucAffector	= DefaultAffector;
	m_fucEmitter	= DefaultEmitter;
	m_fucRemover	= DefaultRemover;
	m_fucRenderer	= DefaultRenderer;
	m_isInitialized = true;
}
void ParticleSystem::SetEmitter(std::function<void(ParticleSystem&, ParticleDescription&)>& emitter)
{
	m_fucEmitter = emitter;
}
void ParticleSystem::SetRemover(std::function<bool(Particle&)>& remover)
{
	m_fucRemover = remover;
}
void ParticleSystem::SetAffector(std::function<void(Particle&)>& affector)
{
	m_fucAffector = affector;
}
void ParticleSystem::SetRenderer(std::function<void(Particle&, sf::RenderWindow&)>& renderer)
{
	m_fucRenderer = renderer;
}

void ParticleSystem::AddParticle(Particle& particle)
{
	m_particleQueue.push_back(particle);
}
void ParticleSystem::SetPosition(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
}

sf::Vector2f ParticleSystem::GetPosition()
{
	return m_pos;
}
void ParticleSystem::Remove_if(std::function<bool(Particle&)> conditionFunc)
{
	auto& it = std::remove_if(m_particleQueue.begin(), m_particleQueue.end(), conditionFunc);
	m_particleQueue.erase(it, m_particleQueue.end());
}
void ParticleSystem::Resume()
{
	m_isEmitting = true;
}

void ParticleSystem::Stop()
{
	m_isEmitting = false;
	ClearParticles();
}

void ParticleSystem::Pause()
{
	m_isEmitting = false;
}

void ParticleSystem::Update()
{
	if (!m_isInitialized) return;

	//remove finished particles
	Remove_if(m_fucRemover);

	ParticleDescription& pd = m_particleDescription;

	//update the particles
	for (auto& particle : m_particleQueue)
	{
		m_fucAffector(particle);
	}

	//if it doesn't stop,then emit particles
	if (m_isEmitting && m_isAlive)
	{
		//it can be create more than 2 particles at the same time
		while (m_emitCounter < pd._emitFrequency)
		{
			m_fucEmitter(*this, m_particleDescription);
			m_emitCounter -= pd._emitFrequency;
		}

		m_emitCounter++;
	}

	if (m_isAlive)
	{
		if (m_systemDuration != 0)
		{
			if (m_systemCounter > m_systemDuration)
			{
				m_isAlive = false;
				m_isEmitting = false;
			}
			m_systemCounter++;
		}
	}
}
void ParticleSystem::Render(sf::RenderWindow& window)
{
	for (auto& particle : m_particleQueue)
	{
		m_fucRenderer(particle,window);
	}
}

void ParticleSystem::ClearParticles()
{
	m_particleQueue.clear();
}

/*
**************************default functions**********************************
*/
void DefaultEmitter(ParticleSystem& ps, ParticleDescription& pd)
{
	int duration = pd._emitDuration + thor::random(-pd._emitDurationRandomness, -pd._emitDurationRandomness);
	sf::Vector2f velocity = thor::rotatedVector(pd._emitVelocity, thor::random(-pd._emitVelocityRandomness, -pd._emitVelocityRandomness));
	sf::Vector2f randomPos(thor::random(-pd._emitPositionRandomness.x, pd._emitPositionRandomness.x),
		thor::random(-pd._emitPositionRandomness.y, pd._emitPositionRandomness.y));
	sf::Vector2f position = ps.GetPosition() + randomPos;
	
	Particle particle;
	particle._sprite = SpriteManager::GetInstance()->CreateSprite(pd._particleTextureName);
	particle._pos = position;
	particle._sprite.setPosition(particle._pos);
	particle._velocity = velocity;
	particle._force = pd._emitForce;
	particle._duration = duration;
	particle._dAngle = pd._angleEnd - pd._angleStart;
	particle._dScale = pd._scaleEnd - pd._scaleStart;
	ps.AddParticle(particle);
}
bool DefaultRemover(Particle& particle)
{
	if (particle._currentLife > particle._duration) return true;
	return false;
}
void DefaultAffector(Particle& particle)
{
	particle._velocity += particle._force;
	particle._pos += particle._velocity;
	particle._sprite.setPosition(particle._pos);

	particle._angle += particle._dAngle;
	particle._sprite.setRotation(particle._angle);

	particle._scale += particle._dScale;
	particle._sprite.setScale(particle._scale, particle._scale);

	particle._currentLife++;
}
void DefaultRenderer(Particle& particle, sf::RenderWindow& window)
{
	window.draw(particle._sprite);
}