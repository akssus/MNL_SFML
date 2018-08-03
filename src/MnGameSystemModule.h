#pragma once
#include <memory>
#include "MnMessageSystem.h"

namespace MNL
{
	class MnGameSystemModule
	{
	public:
		MnGameSystemModule();
		virtual ~MnGameSystemModule();

		virtual void OnRegistered();
		virtual void OnUnregistering();
		virtual void Update();

		std::shared_ptr<MnMessageReceiver> GetMessageReceiver();

		void SetModuleOrder(int32_t order);
		int32_t GetModuleOrder() const;
		

	private:
		[[deprecated]] void _RegisterSelf();
		void _UnregisterSelf();

	private:
		std::shared_ptr<MnMessageReceiver> m_spMessageReceiver;
		int32_t m_moduleOrder; /// 낮을수록 우선순위가 높음
	};
}
