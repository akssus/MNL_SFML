#pragma once
#include <list>
#include <string>
#include "ParticleSystem.h"


/*
if you dont want to let manager manage the particle systems,like you want to adjust the drawing point,
then directly create ParticleSystem instance and manage it by yourself.
If you want to simply spread particles and remove it when it finished, 
let manager class manage the particle system.
please avoid letting the manager class draw the particle system with infinite duration.
*/

namespace MNL
{
	class ParticleManager
	{
	private:
		ParticleManager();
		~ParticleManager();

	public:
		static ParticleManager*	getInstance();
		void freeInstance();

		/*create a particle system with description
		@return copy of particle system*/
		ParticleSystem	createParticleSystem(ParticleDescription& desc);
		/*load particle data from file and bind it to description table
		@return copy of particle system*/
		ParticleSystem	createParticleSystem(std::wstring jsonFileName);
		/*let manager class draw and destroy it automatically*/
		void			spreadParticleSystem(ParticleSystem& ps);
		void			createAndSpreadParticleSystem(ParticleDescription& desc);
		void			createAndSpreadParticleSystem(std::wstring jsonFileName);


		void clearParticleSystems();
		void update();
		void render(sf::RenderWindow& window);
		
	private:
		static ParticleManager*		m_pInstance;
		std::list<ParticleSystem>	m_particleSystemQueue;
		std::map<std::wstring, ParticleDescription> m_particleDescTable;
	};

};