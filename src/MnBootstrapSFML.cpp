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
		//추가 ㄱㄱ싱
		//뭐 기본적으로 게임의 루프는 인풋->업데이트->렌더 잖아? 
		//죄다 모듈로 만들어 버립시다.


		const uint32_t windowWidth = 640;
		const uint32_t windowHeight = 480;
		const std::string title = "mySFMLGame";

		//플랫폼 모듈
		m_spGameSystem->RegisterModule(std::make_shared<MnSFMLModule>(windowWidth, windowHeight, title), MN_MODULE_ORDER_PLATFORM);

		//코어 모듈
		m_spGameSystem->RegisterModule(std::make_shared<MnInputModule>(), MN_MODULE_ORDER_PRE_PROCESS);
		m_spGameSystem->RegisterModule(std::make_shared<MnGameUpdateModule>(), MN_MODULE_ORDER_CORE);
		m_spGameSystem->RegisterModule(std::make_shared<MnRenderModuleSFML>(), MN_MODULE_ORDER_POST_PROCESS );
	}
}
