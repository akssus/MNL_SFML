#pragma once
#include "MnRenderModule.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace MNL
{
	class MnRenderableSFML : MnRenderable
	{
	public:
		MnRenderableSFML();
		std::shared_ptr<sf::Drawable> m_spDrawable;
	};

	class MnRendererSFML : MnRenderer
	{
	public:
		MnRendererSFML();
		void SetRenderWindow(sf::RenderWindow* pRenderWindow);
		void Render(const std::shared_ptr<MnRenderable>& spRenderable) override;

	private:
		sf::RenderWindow* m_pRenderWindow;
	};

	class MnRenderModuleSFML : MnRenderModule
	{
	public:
		void OnRegistered() override;

	};
}
