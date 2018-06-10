#pragma once
#include <memory>


namespace MNL
{
	template <typename T>
	class MnSingleton
	{
	public:
		static std::shared_ptr<T> GetInstance()
		{
			if (m_spInstance == nullptr)
			{
				m_spInstance = std::make_shared<T>();
			}
			return m_spInstance;
		}

		static void FreeInstance()
		{
			m_spInstance.~shared_ptr();
			m_spInstance = nullptr;
		}
	private:
		static std::shared_ptr<T> m_spInstance;
	};

	template<typename T>
	std::shared_ptr<T> MnSingleton::m_spInstance = nullptr;

}