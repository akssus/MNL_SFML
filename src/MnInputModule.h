#pragma once

#include "MnGameSystemModule.h"
#include <unordered_map>
#include "MnGameSystem.h"

namespace MNL
{
	struct MnInputUnit
	{
		uint32_t keyID;
	};


	class MnInputMapper
	{
	public:
		void Register(const std::string& keyName, uint32_t keyID);
		void Unregister(const std::string& keyName);
		MnInputUnit Get(const std::string& keyName);

	private:
		std::unordered_map<std::string, MnInputUnit> m_registeredKeyCodes;
	};

	class MnInputModule : public MnGameSystemModule
	{
	public:
		MnInputModule() = default;
		virtual ~MnInputModule() = default;

	public:
		void OnRegistered() override;
		void Update() override;
	};

	//static 전용 클래스
	class MnInput
	{
	public:
		MnInput();

		//계속 눌리고 있는지 판단
		static bool IsKeyDown(const std::string& keyName);
		static bool IsKeyUp(const std::string& keyName);

	private:
		std::shared_ptr<MnInputModule> m_spInputModule;
	};
}
