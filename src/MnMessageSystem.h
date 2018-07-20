#pragma once
#include <queue>
#include <map>
#include <functional>
#include <memory>

namespace MNL
{

	//---------------------------------------------
	// 메시지
	//---------------------------------------------

	class MnMessage
	{
	protected:
		MnMessage() = default;
	public:
		//즉발성. Dispatch와 동시에 모든 리시버들에게 메시지가 전달됨.
		//큐에 넣어서 한번에 처리하는걸로 해볼까 했는데 구현이 너무 어려워서리
		void Dispatch();

	private:
		//new 할당 금지
		void* operator new(size_t) { return new MnMessage();  }
		void* operator new[](size_t size) { return new MnMessage[size]; }
	};


	//---------------------------------------------
	// 메시지 리시버
	//---------------------------------------------

	class MnMessageReceiver
	{
	public:
		MnMessageReceiver();

		// @brief std::bind(func, *this) 와 같이 사용할것
		template <typename T>
		bool RegisterHandler(const std::function<void(const T*)>& handler) //T*인 이유는 메시지를 상속받아서 구현해야 하므로
		{
			std::string key = typeid(T).raw_name();
			if (m_tblHandlers.find(key) == m_tblHandlers.end())
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


	//---------------------------------------------
	// 메시지 시스템
	//---------------------------------------------

	class MnMessageSystem
	{
	public:
		void Register(const std::string& msgKey, const std::shared_ptr<MnMessageReceiver>& spMessageReceiver);
		//그냥 리시버 자체를 테이블에서 싹 지움
		void Unregister(const std::shared_ptr<MnMessageReceiver>& spMessageReceiver);
		//특정 키에서만 리시버를 제거
		void Unregister(const std::string& msgKey, const std::shared_ptr<MnMessageReceiver>& spMessageReceiver);

		void Distribute(const std::string& msgKey, const MnMessage* pMessage);

	private:
		void _AssureMessageBucket(const std::string& msgKey);

	private:
		std::map<std::string, std::vector<std::shared_ptr<MnMessageReceiver>>> m_tblReceivers;
	};

}
