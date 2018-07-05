/*
* 렌더모듈은 말그대로 렌더링을 담당합니당
* 게임시스템 모듈중 필수적인놈
*/

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

	class MnRenderModule : public MnGameSystemModule
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