#pragma once
#include <memory>
namespace MNL
{
	class MnGameSystem;
	class MnBootstrap
	{
	public:
		virtual ~MnBootstrap() = default;

		//�������̵� �ؼ� �����սô�
		virtual void RegisterModules(MnGameSystem& gameSystem) = 0;
	};
}
