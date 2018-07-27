#pragma once
#include "MnGameObjectComponent.h"
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <list>


namespace MNL
{
	namespace GOComponents
	{
		class Transform : public MnGameObjectComponent
		{
		public:
			sf::Vector2f Position();
			//degree
			float Rotation();
			sf::Vector2f Scale();
			
		private:
			sf::Vector2f m_position;
			float m_rotation;
			sf::Vector2f m_scale;
		};
	}
}
