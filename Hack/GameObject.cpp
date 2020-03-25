#include "GameObject.h"
#include "Console.h"

namespace Scholzf
{

	UnitType GameObject::GetType()
	{
		__try
		{
			if (this == nullptr)
				return UnitType::Unknown;

			auto unitType = *reinterpret_cast<UnitType**>(this + static_cast<int>(Offsets::GameObject::Type));
			if (unitType != nullptr)
			{
				return *static_cast<UnitType*>(unitType);
			}
		}
		__except (1)
		{
			Console::PrintLn("Native Exception thrown at: const Native::GameObject::GetType() &");
		}

		return UnitType::Unknown;
	}

	short* GameObject::GetIndex()
	{
		return reinterpret_cast<short*>(this + 0x8);
	}

	GameObjectVTable* GameObject::GetVirtual()
	{
		return reinterpret_cast<GameObjectVTable*>(this);
	}

	inline char* GetStr(DWORD offset) {
		if (*(int*)(offset + 0x10) > 15)
			return (char*)(*(DWORD*)offset);
		else
			return (char*)offset;
	}

	char* GameObject::GetChampionName() {
		return GetStr((DWORD)this + static_cast<int>(Offsets::Obj_AIHero::ChampionName));
	}

	char* GameObject::GetName() {
		return GetStr((DWORD)this + static_cast<int>(Offsets::GameObject::Name));
	}

	std::string GameObject::GetName2()
	{
		if (this == nullptr)
		{
			return "Unknown";
		}

		if (reinterpret_cast<DWORD*>(this + static_cast<int>(Offsets::GameObject::Name)) == nullptr)
		{
			return "Unknown";
		}
		return *reinterpret_cast<std::string*>(this + static_cast<int>(Offsets::GameObject::Name));
	}

	void GameObject::SetName(std::wstring name)
	{
		*reinterpret_cast<std::wstring*>(this + static_cast<int>(Offsets::GameObject::Name)) = name;
	}

	uint* GameObject::GetNetworkId()
	{
		return reinterpret_cast<uint*>(this + static_cast<int>(Offsets::GameObject::NetworkId));
	}

	//Lua API
	void GameObject::ExportFunctions()
	{
		/*luabind::module(Lua::LuaState)
			[
				class_<GameObject>( "GameObject" )
					.property("Name", &GameObject::GetName)
			];*/
	}

}