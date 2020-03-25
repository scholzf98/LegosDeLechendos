
#include "StaticEnums.h"
#include <vector>
#include "Detour.hpp"
#include "Utils.h"
//#include "AIHeroClient.h"
#include "ObjectManager.h"
#include "Patchables.h"

namespace Scholzf
{

	AIHeroClient* ObjectManager::GetPlayer()
	{
		return *reinterpret_cast<AIHeroClient**>(Patchables::g_localPlayer);
	}

	uint ObjectManager::GetMaxSize()
	{
		return *reinterpret_cast<int*>(Patchables::g_objectManagerMaxSize);
	}

	uint ObjectManager::GetUsedIndexes()
	{
		return *reinterpret_cast<uint*>(Patchables::g_objectManagerUsedIndexes);
	}

	uint ObjectManager::GetHighestPlayerId()
	{
		return *reinterpret_cast<uint*>(MAKE_RVA(Offsets::ObjectManager::HighestPlayerObjectId));
	}

	GameObject** ObjectManager::GetUnitArray()
	{
		return *reinterpret_cast<GameObject***>(Patchables::g_objectManagerUnitArray);
	}

	ObjectManager* GetInstance()
	{
		return reinterpret_cast<ObjectManager*>(MAKE_RVA(Offsets::ObjectManager::ObjectManager));
	}

	GameObject* ObjectManager::GetFirstObject()
	{
		typedef GameObject* (__thiscall* fnGetFirst)(void*);
		return ((fnGetFirst)(MAKE_RVA(0x2AAE10)))(*(void**)MAKE_RVA(Offsets::ObjectManager::ObjectManager));
	}

	GameObject* ObjectManager::GetNextObject(GameObject* object)
	{
		typedef GameObject* (__thiscall* fnGetNext)(void*, GameObject*);
		return ((fnGetNext)(MAKE_RVA(0x2AC0E0)))(*(void**)MAKE_RVA(Offsets::ObjectManager::ObjectManager), object);
	}

	short ObjectManager::GetHighestObjectId()
	{
		short idx = 0;

		Console::PrintLn("printed");

		void* c = GetUnitArray()[idx];
		while ((uintptr_t)c != 0x1) 
		{
			c = GetUnitArray()[++idx];
		}

		Console::PrintLn("idx: %i", idx);

		return idx;
	}

	r3dRenderer* ObjectManager::GetRenderer()
	{
		return *reinterpret_cast<r3dRenderer**>(Patchables::g_r3dRendererInstance);
	}

	GameObject* ObjectManager::GetObjectById(int id)
	{
		auto object = GetUnitArray()[id];
		return object;
	}

}