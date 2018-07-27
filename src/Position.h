#pragma once
#include "MnGameObjectComponent.h"
#include <SFML/System/Vector2.hpp>

namespace MNL
{
	namespace Components
	{
		class Position : public MnGameObjectComponent
		{
		public:
			void Update() override;

			sf::Vector2f m_position;
			
		};
	}
}
