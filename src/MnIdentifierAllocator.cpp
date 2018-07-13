#include "MnIdentifierAllocator.h"
#include <algorithm>

using namespace MNL;

const MnUINT32_ID MnIdentifierAllocator::UNALLOCATED = 0xFFFFFFFF;

MnIdentifierAllocator::MnIdentifierAllocator(MnUINT32_ID idRangeFrom, MnUINT32_ID idRangeTo)
	:m_idRangeFrom(0),
	m_idRangeTo(0),
	m_idOffset(0),
	m_numAllocated(0)
{
	try
	{
		if (idRangeFrom > idRangeTo) throw std::range_error("invaild id range");

		m_idRangeFrom = idRangeFrom;
		m_idRangeTo = idRangeTo;
		m_idOffset = idRangeFrom;

		auto poolSize = m_idRangeTo - m_idRangeFrom + 1;
		m_lstIdentifiers.resize(poolSize, MN_ID_UNALLOCATED);
	}
	catch(std::exception e)
	{
		//DebugLogger.print(e.what());
	}
}

MnIdentifierAllocator::~MnIdentifierAllocator()
{

}

bool MnIdentifierAllocator::IsAllocated(MnUINT32_ID id)
{
	auto index = _ConvertToIndex(id);
	auto state = m_lstIdentifiers[index];
	return state == MN_ID_ALLOCATED;
}

bool MnIdentifierAllocator::IsFull()
{
	return m_numAllocated >= PoolSize();
}

MnUINT32_ID MnIdentifierAllocator::Allocate()
{
	return AllocateAbove(m_idRangeFrom);
}

MnUINT32_ID MnIdentifierAllocator::AllocateAbove(MnUINT32_ID id)
{
	if (id > m_idRangeTo) return UNALLOCATED;

	auto unallocatedID = _FindUnallocated(id, m_idRangeTo);
	if(unallocatedID != UNALLOCATED)
	{
		_AllocateAt(unallocatedID);
	}
	return unallocatedID;
}

uint32_t MnIdentifierAllocator::PoolSize()
{
	return m_idRangeTo - m_idRangeFrom;
}

void MnIdentifierAllocator::Reset()
{
	std::for_each(m_lstIdentifiers.begin(), m_lstIdentifiers.end(), 
		[](auto& state)
		{
			state = MN_ID_UNALLOCATED;
		}
	);
}

MnIdentifierAllocator::MnIdentifierAllocator()
{
	throw std::exception("invaild instancing of MnIdentifierAllocator");
}

//========================================================================================
//PRIVATES
//========================================================================================

uint32_t MnIdentifierAllocator::_ConvertToIndex(MnUINT32_ID id)
{
	return id - m_idOffset;
}

MnUINT32_ID MnIdentifierAllocator::_ConvertToID(uint32_t index)
{
	return index + m_idOffset;
}

MnUINT32_ID MnIdentifierAllocator::_FindUnallocated(MnUINT32_ID from, MnUINT32_ID to)
{
	auto idxFrom = _ConvertToIndex(from);
	auto idxTo = _ConvertToIndex(to);
	auto it = std::find(m_lstIdentifiers.begin() + idxFrom, m_lstIdentifiers.begin() + idxTo, MN_ID_UNALLOCATED);

	if(it != m_lstIdentifiers.end())
	{
		auto index = std::distance(m_lstIdentifiers.begin(), it);
		return _ConvertToID(index);
	}

	return UNALLOCATED;
}

void MnIdentifierAllocator::_AllocateAt(MnUINT32_ID id)
{
	auto idx = _ConvertToIndex(id);
	m_lstIdentifiers[idx] = MN_ID_ALLOCATED;
	m_numAllocated++;
}

void MnIdentifierAllocator::_DeallocateAt(MnUINT32_ID id)
{
	auto idx = _ConvertToIndex(id);
	m_lstIdentifiers[idx] = MN_ID_UNALLOCATED;
	m_numAllocated--;
}
