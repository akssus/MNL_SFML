#include "MnRenderModuleSFML.h"
#include "MnGameSystem.h"
#include "MnSFMLModule.h"

using namespace MNL;


MnRenderableSFML::MnRenderableSFML() : m_spDrawable(std::shared_ptr<sf::Drawable>())
{
}

MnRendererSFML::MnRendererSFML()
{
}

void MnRendererSFML::SetRenderWindow(const std::shared_ptr<sf::RenderWindow>& spRenderWindow)
{
	if(spRenderWindow != nullptr)
	{
		m_spRenderWindow = spRenderWindow;
	}
}

void MnRendererSFML::Render(const std::shared_ptr<MnRenderableSFML>& spRenderable)
{
	if (spRenderable != nullptr)
	{
		m_spRenderWindow->draw(*(spRenderable->m_spDrawable));
	}
}

MnRenderModuleSFML::MnRenderModuleSFML() : m_spRenderer(std::make_shared<MnRendererSFML>())
{
	auto sfmlModule = MnGameSystem::GetInstance()->GetModule<MnSFMLModule>();
	if(sfmlModule != nullptr)
	{
		m_spRenderer->SetRenderWindow(sfmlModule->GetRenderWindow());
	}
}

void MnRenderModuleSFML::OnRegistered()
{
}

void MnRenderModuleSFML::OnUnregistering()
{
}

void MnRenderModuleSFML::Update()
{
}

void MnRenderModuleSFML::SetRenderer(const std::shared_ptr<MnRendererSFML>& spRenderer)
{
	m_spRenderer = spRenderer;
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
		std::for_each(m_renderQueue.begin(), m_renderQueue.end(), [&](const std::shared_ptr<MnRenderableSFML>& spRenderable)
		{
			m_spRenderer->Render(spRenderable);
		});
	}
}

