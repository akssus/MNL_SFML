#include "MnGameObject.h"

using namespace MNL;

MnGameObject::MnGameObject()
{
	//게임오브젝트는 기본적으로 트랜스폼을 가지고있다.
	AddComponent(std::make_shared<GOComponents::Transform>());
}

MnGameObject::~MnGameObject()
{
}


void MnGameObject::AddComponent(const std::shared_ptr<MnGameObjectComponent>& spComponent)
{
	if (spComponent != nullptr)
	{
		m_lstComponents.push_back(spComponent);
	}
}

std::shared_ptr<MnGameObjectComponent> MnGameObject::GetComponent(const std::string& classRawName)
{
	auto it = std::find(m_lstComponents.begin(),m_lstComponents.end(),[&](const std::shared_ptr<MnGameObjectComponent>& spComponent)
	{
		return classRawName == typeid(*spComponent.get()).raw_name();
	});
	return it == m_lstComponents.end() ? nullptr : *it;
}

std::vector<std::shared_ptr<MnGameObjectComponent>>& MnGameObject::GetComponents()
{
	return m_lstComponents;
}

std::shared_ptr<GOComponents::Transform> MnGameObject::Transform()
{
	return GetComponent<GOComponents::Transform>();
}

void MnGameObject::Update()
{
}

void MnGameObject::PreUpdate()
{
}

void MnGameObject::PostUpdate()
{
}

void MnGameObject::OnAwake()
{
}

void MnGameObject::OnDestroy()
{
}
