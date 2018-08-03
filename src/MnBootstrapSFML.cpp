#include "MnBootstrapSFML.h"
#include "MnGameSystem.h"
#include "MnRenderModuleSFML.h"
#include "MnGameUpdateModule.h"
#include "MnSFMLModule.h"
#include "MnInputModuleSFML.h"
#include "MnDebugModule.h"

using namespace MNL;

void MnBootstrapSFML::RegisterModules(MnGameSystem& gameSystem)
{

	//�߰� ������
	//�� �⺻������ ������ ������ ��ǲ->������Ʈ->���� �ݾ�? 
	//�˴� ���� ����� �����ô�.


	const uint32_t windowWidth = 640;
	const uint32_t windowHeight = 480;
	const std::string title = "mySFMLGame";

	//����Ŵ� ���� ó����. ������� �׳� ���� �ǰ��� �� �ƴϸ� �ΰ�ü ������
	gameSystem.RegisterModule(std::make_shared<MnDebugModule>(), MN_MODULE_ORDER_POST_PROCESS);
	MnDebug::SetDebugModule(gameSystem.GetModule<MnDebugModule>());

	//�÷��� ���
	gameSystem.RegisterModule(std::make_shared<MnSFMLModule>(windowWidth, windowHeight, title), MN_MODULE_ORDER_PLATFORM);

	//�ھ� ���
	gameSystem.RegisterModule(std::make_shared<MnInputModuleSFML>(), MN_MODULE_ORDER_PRE_PROCESS);
	MnInput::SetInputModule(gameSystem.GetModule<MnInputModuleSFML>());
	gameSystem.RegisterModule(std::make_shared<MnGameUpdateModule>(), MN_MODULE_ORDER_CORE);
	gameSystem.RegisterModule(std::make_shared<MnRenderModuleSFML>(), MN_MODULE_ORDER_POST_PROCESS );

	//�⺻������ ���ư� �غ� �Ϸ�!!! ��.. �� ��������

}
