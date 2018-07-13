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

		//id가 이미 할당 되었는지 판단
		bool IsAllocated(MnUINT32_ID id);

		//더이상 할당할 공간이 없는지 판단
		bool IsFull();

		//id풀에서 하나 배분, 공간이 없으면 0xFFFFFFFF 반환
		MnUINT32_ID Allocate();

		//해당 id보다 큰 첫번째 id를 할당
		MnUINT32_ID AllocateAbove(MnUINT32_ID id);

		uint32_t PoolSize();

		//할당된 모든 ID정보를 다 날려버리고 UNALLOCATED 상태로 만듬
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