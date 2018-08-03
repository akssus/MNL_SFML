#pragma once
#include "MnGameObject.h"

namespace MNL
{
	//Ŭ������ �ƴϴ� ���ӽ����̽��� ��
	namespace GameObjectFactory
	{
		//������ ���ÿ� ������Ʈ ��⿡ ���
		std::shared_ptr<MnGameObject> Create();

		//������Ʈ ��⿡�� ����
		void Destroy(const std::shared_ptr<MnGameObject>& spGameObject);

	}
}
