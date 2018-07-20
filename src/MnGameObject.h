#pragma once
#include <vector>
#include "MnGameObjectComponent.h"


namespace MNL
{
	class MnGameObject : public MnUpdatable
	{
	public:
		MnGameObject() = default;
		virtual ~MnGameObject() = default;

		void Update() override;
		void PreUpdate() override;
		void PostUpdate() override;

		void OnAwake() override;
		void OnDestroy() override;

	private:
		std::vector<MnGameObjectComponent> m_lstComponents;
	};
}