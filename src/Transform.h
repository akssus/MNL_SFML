#pragma once
#include "MnGameObjectComponent.h"
#include "MnMath.h"
#include <memory>
#include <list>


namespace MNL
{
	namespace GOComponents
	{
		class Transform : public MnGameObjectComponent
		{
		public:
			Transform();

			Math::MnVector2 position;
			float rotation;
			Math::MnVector2 scale;
		};
	}
}
