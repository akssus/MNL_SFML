/*
 * SFML 전용 렌더모듈
 *
 */

#pragma once
#include "MnRenderModule.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

namespace MNL
{
	class MnRenderableSFML : public MnRenderable
	{
	public:
		MnRenderableSFML();
		std::shared_ptr<sf::Drawable> m_spDrawable;
	};

	class MnRendererSFML : public MnRenderer
	{
	public:
		MnRendererSFML();
		void SetRenderWindow(sf::RenderWindow* pRenderWindow);
		void Render(const std::shared_ptr<MnRenderableSFML>& spRenderable);

	private:
		sf::RenderWindow* m_pRenderWindow;
	};

	class MnRenderModuleSFML : public MnRenderModule
	{
	public:
		MnRenderModuleSFML();

	public:
		void SetRenderer(const std::shared_ptr<MnRendererSFML>& spRenderer);
		void AddQueue(const std::shared_ptr<MnRenderable>& spRenderable) override;
		void Render() override;

	private:
		std::shared_ptr<MnRendererSFML> m_spRenderer;
		std::vector<std::shared_ptr<MnRenderableSFML>> m_renderQueue;
	};
}
