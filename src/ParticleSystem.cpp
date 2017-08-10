#include "ParticleSystem.h"

using namespace MNL;



ParticleSystem::ParticleSystem()
{
}


ParticleSystem::~ParticleSystem()
{
	m_particleQueue.clear();
}
void ParticleSystem::initSystem(ParticleDescription& desc)
{
	m_particleDescription = desc;
	m_funAffector	= defaultAffector;
	m_funEmitter	= defaultEmitter;
	m_funRemover	= defaultRemover;
	m_funRenderer	= defaultRenderer;
	m_isInitialized = true;
}
void ParticleSystem::setEmitter(std::function<void(ParticleSystem&, ParticleDescription&)>& emitter)
{
	m_funEmitter = emitter;
}
void ParticleSystem::setRemover(std::function<bool(Particle&)>& remover)
{
	m_funRemover = remover;
}
void ParticleSystem::setAffector(std::function<void(Particle&)>& affector)
{
	m_funAffector = affector;
}
void ParticleSystem::setRenderer(std::function<void(Particle&, sf::RenderWindow&)>& renderer)
{
	m_funRenderer = renderer;
}

void ParticleSystem::addParticle(Particle& particle)
{
	m_particleQueue.push_back(particle);
}
void ParticleSystem::setPosition(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
}

sf::Vector2f ParticleSystem::getPosition()
{
	return m_pos;
}
void ParticleSystem::remove_if(std::function<void(Particle&)> conditionFunc)
{
	std::remove_if(m_particleQueue.begin(), m_particleQueue.end(), conditionFunc);
}
void ParticleSystem::resume()
{
	m_isEmitting = true;
}

void ParticleSystem::stop()
{
	m_isEmitting = false;
	clearParticles();
}

void ParticleSystem::pause()
{
	m_isEmitting = false;
}

void ParticleSystem::update()
{
	if (!m_isInitialized) return;
	//remove finished particles
	remove_if(m_funRemover);

	ParticleDescription& pd = m_particleDescription;

	for (auto& particle : m_particleQueue)
	{
		m_funAffector(particle);
	}

	if (m_isEmitting)
	{
		if (m_emitCounter > pd._emitFrequency)
		{
			m_funEmitter(*this, m_particleDescription);
			m_emitCounter = 0;
		}

		m_emitCounter++;
	}
}
void ParticleSystem::render(sf::RenderWindow& window)
{
	for (auto& particle : m_particleQueue)
	{
		m_funRenderer(particle,window);
	}
}

void ParticleSystem::clearParticles()
{
	m_particleQueue.clear();
}

/*
**************************default functions**********************************
*/
void defaultEmitter(ParticleSystem& ps, ParticleDescription& pd)
{
	int duration = pd._emitDuration + thor::random(-pd._emitDurationRandomness, -pd._emitDurationRandomness);
	sf::Vector2f velocity = thor::rotatedVector(pd._emitVelocity, thor::random(-pd._emitVelocityRandomness, -pd._emitVelocityRandomness));
	sf::Vector2f randomPos(thor::random(-pd._emitPositionRandomness.x, pd._emitPositionRandomness.x),
		thor::random(-pd._emitPositionRandomness.y, pd._emitPositionRandomness.y));
	sf::Vector2f position = ps.getPosition() + randomPos;
	
	Particle particle;
	particle._sprite = SpriteManager::getInstance()->createSprite(pd._particleTextureName);
	particle._pos = position;
	particle._sprite.setPosition(particle._pos);
	particle._velocity = velocity;
	particle._force = pd._emitForce;
	particle._duration = duration;
	particle._dAngle = pd._angleEnd - pd._angleStart;
	particle._dScale = pd._scaleEnd - pd._scaleStart;
	ps.addParticle(particle);
}
bool defaultRemover(Particle& particle)
{
	if (particle._currentLife > particle._duration) return true;
	return false;
}
void defaultAffector(Particle& particle)
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
void defaultRenderer(Particle& particle, sf::RenderWindow& window)
{
	window.draw(particle._sprite);
}