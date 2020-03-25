#pragma once
#include "Offsets.h"
#include "Macros.h"
#include <string>
#include <vector>
#include "Vector3f.h"
#include <Windows.h>

namespace Scholzf
{
	class GameObjectVTable;

#pragma pack(push, 1)
	struct BBox
	{
		float MinimumX;
		float MinimumY;
		float MinimumZ;
		float MaximumX;
		float MaximumY;
		float MaximumZ;
	};

	template< typename Function > Function CallVirtual(PVOID Base, DWORD Index)
	{
		PDWORD* VTablePointer = (PDWORD*)Base;
		PDWORD VTableFunctionBase = *VTablePointer;
		DWORD dwAddress = VTableFunctionBase[Index];

		return (Function)(dwAddress);
	}

	class GameObject
	{
	public:
		GameObjectVTable* GetVirtual();

		UnitType GetType();
		short* GetIndex();
		uint* GetNetworkId();

		MAKE_GET(LocalIndex, int, 0x8);

		Vector3f GetPosition()
		{
			if (this == nullptr)
			{
				return Vector3f(0, 0, 0);
			}

			auto vec = reinterpret_cast<Vector3f*>(this + static_cast<int>(Offsets::GameObject::Position));
			if (vec == nullptr)
			{
				return Vector3f(0, 0, 0);
			}
			return Vector3f(vec->GetX(), vec->GetY(), vec->GetZ());
		}

		Vector3f GetServerPosition()
		{
			if (this == nullptr)
			{
				return Vector3f(0, 0, 0);
			}

			auto vec = reinterpret_cast<Vector3f*>(this + static_cast<int>(Offsets::GameObject::ServerPosition));
			if (vec == nullptr)
			{
				return Vector3f(0, 0, 0);
			}

			return Vector3f(vec->GetX(), vec->GetY(), vec->GetZ());
		}

		float GetBoundingRadius() {
			typedef float(__thiscall* OriginalFn)(PVOID);
			return CallVirtual<OriginalFn>(this, 36)(this);
		}

		bool IsMissile()
		{
			if (this == nullptr)
			{
				return false;
			}

			return GetType() == UnitType::MissileClient;
		}

		char* GetChampionName();
		char* GetName();

		std::string GetName2();
		void SetName(std::wstring);

		bool* GetIsDead()
		{
			return reinterpret_cast<bool*>(this + static_cast<int>(Offsets::GameObject::IsDead));
		}

		MAKE_GET(Team, uint, Offsets::GameObject::Team);
		MAKE_GET(IsVisible, bool, Offsets::GameObject::VisibleOnScreen);
		MAKE_GET(VisibleOnScreen, bool, Offsets::GameObject::VisibleOnScreen);
		MAKE_GET(BBox, BBox, Offsets::GameObject::BBox);
		MAKE_GET(Range, float, Offsets::GameObject::Range);

		//Lua API
		static void ExportFunctions();
	};
}