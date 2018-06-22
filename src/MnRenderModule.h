#pragma once
#include "MnGameSystemModule.h"
#include <queue>

namespace MNL
{
	class MnRenderable
	{
	public:
		virtual ~MnRenderable() = default;
	};

	class MnRenderer
	{
	public:
		virtual ~MnRenderer() = default;
		virtual void Render(const std::shared_ptr<MnRenderable>& spRenderable) = 0;
	};

	class MnRenderModule : MnGameSystemModule
	{
	public:
		void SetRenderer(const std::shared_ptr<MnRenderer>& spRenderer);
		void AddQueue(const std::shared_ptr<MnRenderable>& spRenderable);

		void Render();

	private:
		std::shared_ptr<MnRenderer> m_spRenderer;
		std::queue<std::shared_ptr<MnRenderable>> m_renderQueue;

	};
}