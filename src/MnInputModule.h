#pragma once

#include "MnGameSystemModule.h"
#include <map>
#include "MnGameSystem.h"

namespace MNL
{
	enum MnKeyState
	{
		MN_KEYSTATE_RELEASED,
		MN_KEYSTATE_PRESSED
	};

	struct MnInputUnit
	{
		uint32_t keyCode;
		MnKeyState keyState;

		MnInputUnit() 
		:keyCode(0u), 
		keyState(MN_KEYSTATE_RELEASED) 
		{ }
	};


	class MnInputMapper
	{
	public:
		//keyCode�� �ߺ��� �� �ִ�. �������� keyName�� �ϳ��� Ű�ڵ带 ����ų ���� �ֱ� ����
		void Register(const std::string& keyName, uint32_t keyCode);
		void Unregister(const std::string& keyName);

		void Set(const std::string& keyName, MnKeyState keyState);
		const MnInputUnit Get(const std::string& keyName);

	private:
		std::map<std::string, MnInputUnit> m_registeredKeyCodes;
	};

	class MnInputModule : public MnGameSystemModule
	{
	public:
		MnInputModule() = default;
		virtual ~MnInputModule() = default;

		void OnRegistered() override;
		void OnUnregistering() override;
		void Update() override;

		void Register(const std::string& keyName, uint32_t keyCode);
		void Unregister(const std::string& keyName);

		virtual MnKeyState GetKeyState(const std::string& keyName);

	protected:
		MnInputMapper m_inputMapper;
	};

	//�������� �����ϱ� ���� static�� Ŭ����
	class MnInput
	{
	public:
		static void SetInputModule(const std::shared_ptr<MnInputModule>& spInputModule);

		//��� ������ �ִ��� �Ǵ�
		static bool IsKeyDown(const std::string& keyName);
		static bool IsKeyUp(const std::string& keyName);

	private:
		static bool m_isInitialized;
		static std::shared_ptr<MnInputModule> m_spInputModule;
	};
}
