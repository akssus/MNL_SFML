#pragma once
#include <list>
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>
#include <Thor/Math.hpp>
#include <Thor/Vectors.hpp>
#include "SpriteManager.h"

namespace MNL
{
	struct ParticleDescription
	{
		std::wstring	_particleTextureName;
		int				_emitFrequency = 0;				//how often particles created
		sf::Vector2f	_emitPositionRandomness;		//randomly emitting offset
		int				_emitDuration = 0;				//how long do a particle lives
		int				_emitDurationRandomness = 0;	//variation of duration, +-randomness
		sf::Vector2f	_emitVelocity;					//initial velocity of particle
		float			_emitVelocityRandomness = 0.0f; //emit direction randomness. it means angle
		sf::Vector2f	_emitForce;						//force that particles receive
		float			_scaleStart	= 1.0f;
		float			_scaleEnd	= 1.0f;
		float			_angleStart	= 0.0f;
		float			_angleEnd	= 0.0f;
	};

	struct Particle
	{
		sf::Vector2f	_pos;
		sf::Vector2f	_velocity;
		sf::Vector2f	_force;
		int				_currentLife = 0;
		int				_duration = 0;
		float			_angle = 0.0f;
		float			_dAngle = 0.0f;
		float			_scale = 0.0f;
		float			_dScale = 0.0f;
		sf::Sprite		_sprite;
		float			_extra[10] = { 0, }; //this is used for extar parameters
	};

	class ParticleSystem
	{
	public:
		ParticleSystem();
		~ParticleSystem();
		/*initSystem initialize with default functions. it can be customized with set functions*/
		void			initSystem(ParticleDescription& desc);
		void			setEmitter(std::function<void(ParticleSystem&, ParticleDescription&)>& emitter);
		void			setRemover(std::function<bool(Particle&)>& remover);
		void			setAffector(std::function<void(Particle&)>& affector);
		void			setRenderer(std::function<void(Particle&, sf::RenderWindow&)>& renderer);

		void			addParticle(Particle& particle);
		void			setPosition(float x, float y);
		sf::Vector2f	getPosition();
		
		void			resume();
		/*	stop removes every particles in the screen	*/
		void			stop();
		/*	pause emitter but unfinished particles still remain	*/
		void			pause();
		
		void			update();
		void			render(sf::RenderWindow& window);

	private:
		void			clearParticles();
		void			remove_if(std::function<void(Particle&)> conditionFunc);

		/* emitter describes when creating a particle, defines initial parameters of the particle */
		std::function<void(ParticleSystem&, ParticleDescription&)>	m_funEmitter;

		/* remover determine whether a particle should be destroyed or not. return true when it should be destroyed */
		std::function<bool(Particle&)>	m_funRemover;

		/* affector define how a particle moves when update particle system */
		std::function<void(Particle&)>	m_funAffector;

		/* renderer renders a particle */
		std::function<void(Particle&,sf::RenderWindow&)>	m_funRenderer;

	private:
		sf::Vector2f		m_pos;
		std::list<Particle> m_particleQueue;
		ParticleDescription m_particleDescription;
		int					m_emitCounter = 0;
		bool				m_isInitialized = false;
		bool				m_isEmitting = true;
		bool				m_colorMode = false;

	};

	void defaultEmitter(ParticleSystem& ps, ParticleDescription& pd);
	bool defaultRemover(Particle& particle);
	void defaultAffector(Particle& particle);
	void defaultRenderer(Particle& particle, sf::RenderWindow& window);


}