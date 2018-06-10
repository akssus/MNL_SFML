#pragma once
#include <list>
#include <string>
#include "ParticleSystem.h"
#include "MnSingleton.h"


/*
if you dont want to let manager manage the particle systems,like you want to adjust the drawing point,
then directly create ParticleSystem instance and manage it by yourself.
If you want to simply spread particles and remove it when it finished, 
let manager class manage the particle system.
please avoid letting the manager class draw the particle system with infinite duration.
*/

namespace MNL
{
	class ParticleManager : public MnSingleton<ParticleSystem>
	{
	private:
		ParticleManager();
		~ParticleManager();

	public:
		/*create a particle system with description
		@return copy of particle system*/
		ParticleSystem	CreateParticleSystem(ParticleDescription& desc);
		/*load particle data from file and bind it to description table
		@return copy of particle system*/
		ParticleSystem	CreateParticleSystem(const std::wstring& jsonFileName);
		/*let manager class draw and destroy it automatically*/
		void			SpreadParticleSystem(ParticleSystem& ps);
		void			CreateAndSpreadParticleSystem(ParticleDescription& desc);
		void			CreateAndSpreadParticleSystem(const std::wstring& jsonFileName);

		void ClearParticleSystems();
		void Update();
		void Render(sf::RenderWindow& window);
		
	private:
		std::list<ParticleSystem>	m_particleSystemQueue;
		std::map<std::wstring, ParticleDescription> m_particleDescTable;
	};

};