#pragma once
#include <vector>

namespace MNL
{
	typedef uint32_t MnUINT32_ID;

	class MnIdentifierAllocator final
	{
	private:
		enum MnIdentifierState
		{
			MN_ID_ALLOCATED,
			MN_ID_UNALLOCATED,
		};
	public:
		MnIdentifierAllocator(MnUINT32_ID idRangeFrom, MnUINT32_ID idRangeTo);
		~MnIdentifierAllocator();

		//id�� �̹� �Ҵ� �Ǿ����� �Ǵ�
		bool IsAllocated(MnUINT32_ID id);

		//���̻� �Ҵ��� ������ ������ �Ǵ�
		bool IsFull();

		//idǮ���� �ϳ� ���, ������ ������ 0xFFFFFFFF ��ȯ
		MnUINT32_ID Allocate();

		//�ش� id���� ū ù��° id�� �Ҵ�
		MnUINT32_ID AllocateAbove(MnUINT32_ID id);

		uint32_t PoolSize();

		//�Ҵ�� ��� ID������ �� ���������� UNALLOCATED ���·� ����
		void Reset();

	public:
		static const MnUINT32_ID UNALLOCATED;

	private:
		MnIdentifierAllocator();

		uint32_t _ConvertToIndex(MnUINT32_ID id);
		MnUINT32_ID _ConvertToID(uint32_t index);

		MnUINT32_ID _FindUnallocated(MnUINT32_ID from, MnUINT32_ID to);
		void _AllocateAt(MnUINT32_ID id);
		void _DeallocateAt(MnUINT32_ID id);

	private:
		MnUINT32_ID m_idRangeFrom;
		MnUINT32_ID m_idRangeTo;
		uint32_t m_idOffset;
		uint32_t m_numAllocated;
		std::vector<MnIdentifierState> m_lstIdentifiers;
	};
}