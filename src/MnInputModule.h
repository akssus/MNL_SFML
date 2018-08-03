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
		//keyCode는 중복될 수 있다. 여러개의 keyName이 하나의 키코드를 가르킬 수도 있기 때문
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

	//전역에서 접근하기 위한 static용 클래스
	class MnInput
	{
	public:
		static void SetInputModule(const std::shared_ptr<MnInputModule>& spInputModule);

		//계속 눌리고 있는지 판단
		static bool IsKeyDown(const std::string& keyName);
		static bool IsKeyUp(const std::string& keyName);

	private:
		static bool m_isInitialized;
		static std::shared_ptr<MnInputModule> m_spInputModule;
	};
}
