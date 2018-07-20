/*
 * �������ͺ� ������Ʈ���� ������Ʈ�� ����� ���� ���� �̻���
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
		//�������̵�
		//*************
		void Update() override;

		//*************
		//Add,Remove
		//*************

		//�ڵ��Ҵ��� ���ϸ� MnIdentifierAllocator::UNALLOCATED �� �ѱ�ð�
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
