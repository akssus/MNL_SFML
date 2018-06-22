#include "MnRenderModuleSFML.h"

using namespace MNL;


MnRenderableSFML::MnRenderableSFML() : m_spDrawable(std::shared_ptr<sf::Drawable>())
{
}

MnRendererSFML::MnRendererSFML():m_pRenderWindow(nullptr)
{
}

void MnRendererSFML::SetRenderWindow(sf::RenderWindow* pRenderWindow)
{
	if(pRenderWindow != nullptr)
	{
		m_pRenderWindow = pRenderWindow;
	}
}

void MnRendererSFML::Render(const std::shared_ptr<MnRenderable>& spRenderable)
{
	if(m_pRenderWindow && spRenderable != nullptr)
	{
		auto sfmlRenderable = std::dynamic_pointer_cast<MnRenderableSFML, MnRenderable>(spRenderable);
		if (sfmlRenderable != nullptr)
		{
			if (sfmlRenderable->m_spDrawable != nullptr)
			{
				m_pRenderWindow->draw(*(sfmlRenderable->m_spDrawable));
			}
		}
	}
}

void MnRenderModuleSFML::OnRegistered()
{
	SetRenderer(std::static_pointer_cast<MnRenderer>(std::make_shared<MnRendererSFML>()));
}
