/*
 * 업데이터블 오브젝트들의 업데이트를 담당함 ㅋㅋ 말이 이상해
 */

#pragma once
#include <vector>
#include <memory>
#include "MnGameSystemModule.h"
#include "MnIdentifierAllocator.h"
#include "MnGameObject.h"

namespace MNL
{
	class MnUpdatableContainer final
	{
	public:
		MnUpdatableContainer();
		MnUpdatableContainer(const std::shared_ptr<MnUpdatable>& spUpdatable, MnUINT32_ID id = 0, MnUINT32_ID order = 0);
		~MnUpdatableContainer();

		std::shared_ptr<MnUpdatable> Updatable();
		MnUINT32_ID ID();
		MnUINT32_ID Order();

		void SetUpdatable(const std::shared_ptr<MnUpdatable> spUpdatable);
		void SetID(const MnUINT32_ID& id);
		void SetOrder(const MnUINT32_ID& order);

	private:
		std::shared_ptr<MnUpdatable> m_spUpdatable;
		uint32_t m_id;
		uint32_t m_order;
	};

	class MnGameUpdateModule : public MnGameSystemModule
	{
	public:
		MnGameUpdateModule();
		 ~MnGameUpdateModule() = default;

	public:
		//*************
		//오버라이드
		//*************
		void Update() override;

		//*************
		//Add,Remove
		//*************

		//자동할당을 원하면 MnIdentifierAllocator::UNALLOCATED 를 넘기시게
		void Add(const std::shared_ptr<MnUpdatable>& spUpdatable, MnUINT32_ID order = MnIdentifierAllocator::UNALLOCATED, MnUINT32_ID id = MnIdentifierAllocator::UNALLOCATED);
		void Remove(const std::shared_ptr<MnUpdatable>& spUpdatable);
		void Remove(const MnUINT32_ID& id);

	private:
		void _PreUpdate();
		void _Update();
		void _PostUpdate();

		void _SortOrder();

	private:
		MnIdentifierAllocator m_idAllocator;
		MnIdentifierAllocator m_orderAllocator;
		std::vector<MnUpdatableContainer> m_lstUpdatables;
		
	};
}
