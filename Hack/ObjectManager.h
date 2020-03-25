#pragma once
#include "Utils.h"
#include "StaticEnums.h"
#include <vector>
#include "Detour.hpp"
#include "r3dRenderer.h"

namespace Scholzf
{
	class AIHeroClient;
	class GameObject;

	class ObjectManager
	{
	public:
		static uint GetMaxSize();
		static uint GetUsedIndexes();
		static short GetHighestObjectId();
		static uint GetHighestPlayerId();
		static GameObject* GetFirstObject();
		static GameObject* GetNextObject(GameObject* object);

		static GameObject** GetUnitArray();
		static GameObject* GetObjectById(int id);
		static AIHeroClient* GetPlayer();

		static r3dRenderer* GetRenderer();
	};
}