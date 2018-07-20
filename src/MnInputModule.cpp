#include "MnInputModule.h"

using namespace MNL;

void MnInputModule::OnRegistered()
{
	
}

void MnInputModule::Update()
{
}

MnInput::MnInput()
{
	m_spInputModule = MnGameSystem::GetInstance()->GetModule<MnInputModule>();
}

bool MnInput::IsKeyDown(const std::string& keyName)
{
	
}

bool MnInput::IsKeyUp(const std::string& keyName)
{

}
