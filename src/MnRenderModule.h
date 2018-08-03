/*
* 렌더모듈은 말그대로 렌더링을 담당합니당
* 게임시스템 모듈중 필수적인놈
* 어쩌다 보니 죄다 인터페이스만을 정의하게됨. 로직을 넣으면 너무 Specific 해지는 문제가 있더라고
*/

#pragma once
#include "MnGameSystemModule.h"

namespace MNL
{
	//현재로선 AddQueue 만을 위한 인터페이스용 클래스
	class MnRenderable
	{
	public:
		virtual ~MnRenderable() = default;
	};

	class MnRenderer
	{
	public:
		virtual ~MnRenderer() = default;
		virtual void Render(const std::shared_ptr<MnRenderable>& spRenderable);
	};

	class MnRenderModule : public MnGameSystemModule
	{
	public:
		virtual ~MnRenderModule() = default;
	public:
		//인터페이스만을 정의한다
		virtual void AddQueue(const std::shared_ptr<MnRenderable>& spRenderable) = 0;
		virtual void Render() = 0;

	};

}