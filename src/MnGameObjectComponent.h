#pragma once

namespace MNL
{
	//������Ʈ ����� �����ϴ� �������̽� �Դϴ�
	//UpdateModule���� �����ϴ� �������̽��̱⵵ �Ԥ�
	class MnUpdatable
	{
	public:
		virtual ~MnUpdatable();

		virtual void Update() = 0;
		virtual void PreUpdate() = 0;
		virtual void PostUpdate() = 0;

		virtual void OnAwake() = 0;
		virtual void OnDestroy() = 0;
	};

	class MnGameObjectComponent : public MnUpdatable
	{
	public:
		void Update() override;
		void PreUpdate() override;
		void PostUpdate() override;

		void OnAwake() override;
		void OnDestroy() override;
	};
}