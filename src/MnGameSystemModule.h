#pragma once
#include <string>
#include <functional>
#include <memory>
#include <map>

namespace MNL
{
	class MnMessage
	{
	protected:
		MnMessage() = default;
	public:
		void Dispatch();
	};

	class MnMessageReceiver
	{
	public:
		// @brief std::bind(func, *this) 와 같이 사용할것
		template <typename T>
		bool RegisterHandler(const std::function<void(const T*)>& handler)
		{
			std::string key = typeid(T).name();
			if(m_tblHandlers.find(key) == m_tblHandlers.end())
			{
				if (std::is_base_of<MnMessage, T>::value)
				{
					m_tblHandlers[key] = handler;
					return true;
				}
			}
			return false;
		}
		void ReceiveMessage(const MnMessage* pMessage);

	private:
		std::map<std::string, std::function<void(const MnMessage*)>> m_tblHandlers;
	};

	class MnGameSystemModule
	{
	public:
		MnGameSystemModule();
		virtual ~MnGameSystemModule();

		virtual void OnRegistered() = 0;
		virtual void OnUnregistering() = 0;
		virtual void Update() = 0;

		//@brief std::bind와 같이 사용할것
		template <typename T>
		void RegisterMessageHandler(const std::function<void(const T*)>& handler)
		{
			m_messageReceiver.RegisterHandler<T>(handler);
		}
		void ReceiveMessage(const MnMessage* pMessage);

		void SetModuleOrder(int32_t order);
		int32_t GetModuleOrder();
		

	private:
		[[deprecated]] void _RegisterSelf();
		void _UnregisterSelf();

	private:
		MnMessageReceiver m_messageReceiver;
		int32_t m_moduleOrder; /// 낮을수록 우선순위가 높음
	};
}
