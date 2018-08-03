#include "MnInputModule.h"
#include <SFML/Window/Event.hpp>

using namespace MNL;

void MnInputMapper::Register(const std::string& keyName, uint32_t keyCode)
{
	m_registeredKeyCodes[keyName] = MnInputUnit();
	m_registeredKeyCodes[keyName].keyCode = keyCode;
}

void MnInputMapper::Unregister(const std::string& keyName)
{
	m_registeredKeyCodes.erase(keyName);
}

void MnInputMapper::Set(const std::string& keyName, MnKeyState keyState)
{
	auto it = m_registeredKeyCodes.find(keyName);
	if (it != m_registeredKeyCodes.end())
	{
		it->second.keyState = keyState;
	}
}

const MnInputUnit MnInputMapper::Get(const std::string& keyName)
{
	auto it = m_registeredKeyCodes.find(keyName);
	if(it != m_registeredKeyCodes.end())
	{
		return it->second;
	}

	return MnInputUnit();
}

void MnInputModule::OnRegistered()
{
}

void MnInputModule::OnUnregistering()
{
}

void MnInputModule::Update()
{
}

void MnInputModule::Register(const std::string& keyName, uint32_t keyCode)
{
	m_inputMapper.Register(keyName, keyCode);
}

void MnInputModule::Unregister(const std::string& keyName)
{
	m_inputMapper.Unregister(keyName);
}

MnKeyState MnInputModule::GetKeyState(const std::string& keyName)
{
	return m_inputMapper.Get(keyName).keyState;
}


bool MnInput::m_isInitialized = false;

void MnInput::SetInputModule(const std::shared_ptr<MnInputModule>& spInputModule)
{
	if (m_spInputModule != nullptr)
	{
		m_spInputModule = spInputModule;
		m_isInitialized = true;
	}
}

bool MnInput::IsKeyDown(const std::string& keyName)
{
	if (!m_isInitialized) { return false; }

	return m_spInputModule->GetKeyState(keyName) == MN_KEYSTATE_PRESSED;
}

bool MnInput::IsKeyUp(const std::string& keyName)
{
	if (!m_isInitialized) { return false; }

	return m_spInputModule->GetKeyState(keyName) == MN_KEYSTATE_RELEASED;
}