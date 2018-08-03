#pragma once

namespace MNL
{
	//업데이트 기능을 정의하는 인터페이스 입니닷
	//UpdateModule에서 참조하는 인터페이스이기도 함ㅋ
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