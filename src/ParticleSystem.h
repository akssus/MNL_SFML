#pragma once
#include <list>
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>

namespace MNL
{
	struct ParticleDescription
	{
		std::wstring	_particleTextureName;
		int				_emitFrequency = 0;				//how often particles created
		int				_systemDuration = 0;			//how long a particle system lives. 0 means infinite
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
		int				_blendMode	= 0;
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
		void			InitSystem(ParticleDescription& desc);
		void			SetEmitter(std::function<void(ParticleSystem&, ParticleDescription&)>& emitter);
		void			SetRemover(std::function<bool(Particle&)>& remover);
		void			SetAffector(std::function<void(Particle&)>& affector);
		void			SetRenderer(std::function<void(Particle&, sf::RenderWindow&)>& renderer);

		void			AddParticle(Particle& particle);
		void			SetPosition(float x, float y);
		sf::Vector2f	GetPosition();
		
		void			Resume();
		/*	stop removes every particles in the screen	*/
		void			Stop();
		/*	pause emitter but unfinished particles still remain	*/
		void			Pause();
		
		void			Update();
		void			Render(sf::RenderWindow& window);

	private:
		void			ClearParticles();
		void			Remove_if(std::function<bool(Particle&)> conditionFunc);

		/* emitter describes when creating a particle, defines initial parameters of the particle */
		std::function<void(ParticleSystem&, ParticleDescription&)>	m_fucEmitter;

		/* remover determine whether a particle should be destroyed or not. return true when it should be destroyed */
		std::function<bool(Particle&)>	m_fucRemover;

		/* affector define how a particle moves when update particle system */
		std::function<void(Particle&)>	m_fucAffector;

		/* renderer renders a particle */
		std::function<void(Particle&,sf::RenderWindow&)>	m_fucRenderer;

	public:
		bool				m_isAlive = true;
	private:
		sf::Vector2f		m_pos;
		std::list<Particle> m_particleQueue;
		ParticleDescription m_particleDescription;
		int					m_emitCounter = 0;
		bool				m_isInitialized = false;
		bool				m_isEmitting = true;
		int					m_systemDuration = 0;
		int					m_systemCounter = 0;
		sf::BlendMode		m_blendMode;
	};

	void DefaultEmitter(ParticleSystem& ps, ParticleDescription& pd);
	bool DefaultRemover(Particle& particle);
	void DefaultAffector(Particle& particle);
	void DefaultRenderer(Particle& particle, sf::RenderWindow& window);


}