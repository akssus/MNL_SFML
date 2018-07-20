#include "MnBootstrapSFML.h"
#include "MnRenderModuleSFML.h"
#include "MnInputModule.h"
#include "MnGameUpdateModule.h"
#include "MnSFMLModule.h"

using namespace MNL;

void MnBootstrapSFML::RegisterModules()
{
	if(m_spGameSystem != nullptr)
	{
		//�߰� ������
		//�� �⺻������ ������ ������ ��ǲ->������Ʈ->���� �ݾ�? 
		//�˴� ���� ����� �����ô�.


		const uint32_t windowWidth = 640;
		const uint32_t windowHeight = 480;
		const std::string title = "mySFMLGame";

		//�÷��� ���
		m_spGameSystem->RegisterModule(std::make_shared<MnSFMLModule>(windowWidth, windowHeight, title), MN_MODULE_ORDER_PLATFORM);

		//�ھ� ���
		m_spGameSystem->RegisterModule(std::make_shared<MnInputModule>(), MN_MODULE_ORDER_PRE_PROCESS);
		m_spGameSystem->RegisterModule(std::make_shared<MnGameUpdateModule>(), MN_MODULE_ORDER_CORE);
		m_spGameSystem->RegisterModule(std::make_shared<MnRenderModuleSFML>(), MN_MODULE_ORDER_POST_PROCESS );
	}
}
