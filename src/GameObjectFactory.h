#pragma once
#include "MnGameObject.h"

namespace MNL
{
	//클래스가 아니다 네임스페이스다 ㅋ
	namespace GameObjectFactory
	{
		//생성과 동시에 업데이트 모듈에 등록
		std::shared_ptr<MnGameObject> Create();

		//업데이트 모듈에서 제거
		void Destroy(const std::shared_ptr<MnGameObject>& spGameObject);

	}
}
