#include "MnRenderModule.h"

using namespace MNL;

void MnRenderModule::SetRenderer(const std::shared_ptr<MnRenderer>& spRenderer)
{
	if (spRenderer != nullptr)
	{
		m_spRenderer = spRenderer;
	}
}

void MnRenderModule::AddQueue(const std::shared_ptr<MnRenderable>& spRenderable)
{
	m_renderQueue.push(spRenderable);
}

void MnRenderModule::Render()
{
	if(m_spRenderer != nullptr)
	{
		while(!m_renderQueue.empty())
		{
			auto spRenderable = m_renderQueue.front();
			m_renderQueue.pop();

			m_spRenderer->Render(spRenderable);
		}
	}
}
