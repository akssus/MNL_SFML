#include "MnBootstrap.h"

MNL::MnBootstrap::MnBootstrap()
{
	m_spGameSystem = MnGameSystem::GetInstance();
}

MNL::MnBootstrap::~MnBootstrap() = default;