#pragma once
#include <queue>
#include <map>
#include <functional>
#include <memory>

namespace MNL
{

	//---------------------------------------------
	// �޽���
	//---------------------------------------------

	class MnMessage
	{
	protected:
		MnMessage() = default;
	public:
		//��߼�. Dispatch�� ���ÿ� ��� ���ù��鿡�� �޽����� ���޵�.
		//ť�� �־ �ѹ��� ó���ϴ°ɷ� �غ��� �ߴµ� ������ �ʹ� ���������
		void Dispatch();

	private:
		//new �Ҵ� ����
		void* operator new(size_t) { return new MnMessage();  }
		void* operator new[](size_t size) { return new MnMessage[size]; }
	};


	//---------------------------------------------
	// �޽��� ���ù�
	//---------------------------------------------

	class MnMessageReceiver
	{
	public:
		MnMessageReceiver();

		// @brief std::bind(func, *this) �� ���� ����Ұ�
		template <typename T>
		bool RegisterHandler(const std::function<void(const T*)>& handler) //T*�� ������ �޽����� ��ӹ޾Ƽ� �����ؾ� �ϹǷ�
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
	// �޽��� �ý���
	//---------------------------------------------

	class MnMessageSystem
	{
	public:
		void Register(const std::string& msgKey, const std::shared_ptr<MnMessageReceiver>& spMessageReceiver);
		//�׳� ���ù� ��ü�� ���̺��� �� ����
		void Unregister(const std::shared_ptr<MnMessageReceiver>& spMessageReceiver);
		//Ư�� Ű������ ���ù��� ����
		void Unregister(const std::string& msgKey, const std::shared_ptr<MnMessageReceiver>& spMessageReceiver);

		void Distribute(const std::string& msgKey, const MnMessage* pMessage);

	private:
		void _AssureMessageBucket(const std::string& msgKey);

	private:
		std::map<std::string, std::vector<std::shared_ptr<MnMessageReceiver>>> m_tblReceivers;
	};

}
