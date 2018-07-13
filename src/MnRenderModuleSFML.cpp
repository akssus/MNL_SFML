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

void MnRendererSFML::Render(const std::shared_ptr<MnRenderableSFML>& spRenderable)
{
	if (spRenderable != nullptr)
	{
		m_pRenderWindow->draw(*(spRenderable->m_spDrawable));
	}
}

MnRenderModuleSFML::MnRenderModuleSFML() : m_spRenderer(std::make_shared<MnRendererSFML>())
{
}

void MnRenderModuleSFML::AddQueue(const std::shared_ptr<MnRenderable>& spRenderable)
{
	auto spRenderableSFML = std::dynamic_pointer_cast<MnRenderableSFML>(spRenderable);
	if (spRenderableSFML != nullptr)
	{
		m_renderQueue.push_back(spRenderableSFML);
	}
}

void MnRenderModuleSFML::Render()
{
	if (m_spRenderer != nullptr)
	{
		std::for_each(m_renderQueue.begin(), m_renderQueue.end(), [](auto& spRenderable)
		{
				m_spRenderer->Render(spRenderable);
		});
	}
}

