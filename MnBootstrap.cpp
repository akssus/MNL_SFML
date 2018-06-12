#include "MnBootstrap.h"

MNL::MnBootstrap::MnBootstrap()
{
	m_spGameSystem = MnGameSystem::GetInstance();
}

MNL::MnBootstrap::~MnBootstrap()
{

}

void MNL::MnBootstrap::RegisterModules()
{
	//m_spGameSystem->RegisterModule( std::make_shared<somemodule>() );
}
