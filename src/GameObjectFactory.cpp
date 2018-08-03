#include "GameObjectFactory.h"
#include "MnGameSystem.h"
#include "MnGameUpdateModule.h"
using namespace MNL;

std::shared_ptr<MnGameObject> GameObjectFactory::Create()
{
	auto spUpdateModule = MnGameSystem::GetInstance()->GetModule<MnGameUpdateModule>();
	if (spUpdateModule == nullptr) { return std::shared_ptr<MnGameObject>(); }

	auto newGameObject = std::make_shared<MnGameObject>();
	spUpdateModule->Add(newGameObject);

	return newGameObject;
}

void GameObjectFactory::Destroy(const std::shared_ptr<MnGameObject>& spGameObject)
{
	auto spUpdateModule = MnGameSystem::GetInstance()->GetModule<MnGameUpdateModule>();
	if (spUpdateModule == nullptr) { return; }

	spUpdateModule->Remove(spGameObject);
}
