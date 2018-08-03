#pragma once
#include <vector>
#include "MnGameObjectComponent.h"
#include <memory>
#include "Transform.h"


namespace MNL
{
	class MnGameObject : public MnUpdatable
	{
	public:
		MnGameObject();
		virtual ~MnGameObject();

		void Update() override;
		void PreUpdate() override;
		void PostUpdate() override;

		void OnAwake() override;
		void OnDestroy() override;

		void AddComponent(const std::shared_ptr<MnGameObjectComponent>& spComponent);
		std::shared_ptr<MnGameObjectComponent> GetComponent(const std::string& classRawName);
		
		template <typename T>
		std::shared_ptr<T> GetComponent()
		{
			std::string classRawName = typeid(T).raw_name();
			std::shared_ptr<MnGameObjectComponent> spComponent = GetComponent(classRawName);
			if(spComponent != nullptr)
			{
				return std::dynamic_pointer_cast<T>(spComponent);
			}
			return nullptr;
		}

		std::vector<std::shared_ptr<MnGameObjectComponent>>& GetComponents();

		//모든 게임오브젝트는 필수적으로 트랜스폼을 가지고 있다.
		std::shared_ptr<GOComponents::Transform> Transform();

	private:
		std::vector<std::shared_ptr<MnGameObjectComponent>> m_lstComponents;
	};
}
