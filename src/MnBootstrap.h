#pragma once
#include <memory>
namespace MNL
{
	class MnGameSystem;
	class MnBootstrap
	{
	public:
		virtual ~MnBootstrap() = default;

		//오버라이드 해서 조립합시다
		virtual void RegisterModules(MnGameSystem& gameSystem) = 0;
	};
}
