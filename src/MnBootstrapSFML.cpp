#include "MnBootstrapSFML.h"
#include "MnRenderModuleSFML.h"

using namespace MNL;

void MnBootstrapSFML::RegisterModules()
{
	if(m_spGameSystem != nullptr)
	{
		m_spGameSystem->RegisterModule(std::make_shared<MnRenderModuleSFML>());
	}
}
