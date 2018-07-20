#include "MnGameUpdateModule.h"
#include <algorithm>

using namespace MNL;

MnUpdatableContainer::MnUpdatableContainer() :
	m_spUpdatable(std::shared_ptr<MnUpdatable>()),
	m_id(0),
	m_order(0)
{
}

MnUpdatableContainer::MnUpdatableContainer(const std::shared_ptr<MnUpdatable>& spUpdatable, MnUINT32_ID id, MnUINT32_ID order) : 
	m_spUpdatable(spUpdatable),
	m_id(id),
	m_order(order)
{
}

MnUpdatableContainer::~MnUpdatableContainer()
{

}

std::shared_ptr<MnUpdatable> MnUpdatableContainer::Updatable()
{
	return m_spUpdatable;
}

MnUINT32_ID MnUpdatableContainer::ID()
{
	return m_id;
}

MnUINT32_ID MnUpdatableContainer::Order()
{
	return m_order;
}

void MnUpdatableContainer::SetUpdatable(const std::shared_ptr<MnUpdatable> spUpdatable)
{
	if (spUpdatable != nullptr)
	{
		m_spUpdatable = spUpdatable;
	}
}

void MnUpdatableContainer::SetID(const MnUINT32_ID& id)
{
	//UINT는 어차피 0 이상임
	m_id = id;
}

void MnUpdatableContainer::SetOrder(const MnUINT32_ID& order)
{
	//UINT는 어차피 0 이상임
	m_order = order;
}

MnGameUpdateModule::MnGameUpdateModule() : m_idAllocator(0,5000), m_orderAllocator(0,5000)
{
	m_lstUpdatables.reserve(m_orderAllocator.PoolSize());
}

void MnGameUpdateModule::Update()
{
	_PreUpdate();
	_Update();
	_PostUpdate();
}

void MnGameUpdateModule::Add(const std::shared_ptr<MnUpdatable>& spUpdatable, MnUINT32_ID order, MnUINT32_ID id)
{
	if(order == MnIdentifierAllocator::UNALLOCATED)
	{
		order = m_orderAllocator.Allocate();
	}
	if(id == MnIdentifierAllocator::UNALLOCATED)
	{
		id = m_idAllocator.Allocate();
	}

	MnUpdatableContainer container(spUpdatable, id, order);
	m_lstUpdatables.push_back(container);
}

void MnGameUpdateModule::Remove(const std::shared_ptr<MnUpdatable>& spUpdatable)
{
	std::remove(m_lstUpdatables.begin(), m_lstUpdatables.end(), spUpdatable);
}

void MnGameUpdateModule::Remove(const MnUINT32_ID& id)
{
	std::remove_if(m_lstUpdatables.begin(),m_lstUpdatables.end(),[&](MnUpdatableContainer& updatable)
	{
		return updatable.ID() == id;
	});
}

void MnGameUpdateModule::_PreUpdate()
{
	for (auto& obj : m_lstUpdatables)
	{
		obj.Updatable()->PreUpdate();
	}
}

void MnGameUpdateModule::_Update()
{
	for (auto& obj : m_lstUpdatables)
	{
		obj.Updatable()->Update();
	}
}

void MnGameUpdateModule::_PostUpdate()
{
	for (auto& obj : m_lstUpdatables)
	{
		obj.Updatable()->PostUpdate();
	}
}

void MnGameUpdateModule::_SortOrder()
{
	std::sort(m_lstUpdatables.begin(), m_lstUpdatables.end(), [](MnUpdatableContainer& updatableA, MnUpdatableContainer& updatableB)
	{
		//오름순 정렬
		return updatableA.Order() < updatableB.Order();
	});
}

