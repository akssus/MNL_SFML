#pragma once
#include "MnGameObjectComponent.h"
#include "MnRenderModule.h"
#include "MnSprite.h"

namespace MNL
{
	namespace GOComponents
	{
		class Sprite : public MnGameObjectComponent
		{
		public:
			void SetImage(std::shared_ptr<MnSprite> spImage);
			std::shared_ptr<MnSprite> GetImage();

		private:
			std::shared_ptr<MnSprite> m_spSprite;
		};
	}
}
