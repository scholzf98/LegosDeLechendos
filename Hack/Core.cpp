#include "Core.h"
#include "Patchables.h"
#include "Detour.hpp"
#include "RiotX3D.h"
#include <time.h>
#include "AIHeroClient.h"
#include "ObjectManager.h"
#include "GameFunctions.h"
#include "r3dRenderer.h"
#include "Macros.h"

namespace Scholzf
{
	int Core::mainModule = 0;

	Core::Core(HMODULE h_module)
	{
		this->hModule = h_module;

		srand(time(nullptr));

		Patchables::Initialize();

		Console::PrintLn("scholzf ( %s %s) loading... ", __TIME__, __DATE__);

		if (!this->ApplyHooks())
		{
			Console::PrintLn("312451723");
		}
		else
		{
			this->DisplayWelcomeMessage();
		}
	}

	Core::~Core()
	{

	}

	void Core::DisplayWelcomeMessage() const
	{
		Console::PrintLn("Welcome");
		AIHeroClient* player = ObjectManager::GetPlayer();
		this->main(player);
	}

	void Core::main(AIHeroClient* player) const
	{

		while (true)
		{
			if (GetAsyncKeyState(VK_LSHIFT) & 1)
			{
				/*
				Console::PrintLn("%f, %f, %f", player->GetPosition().GetX(), player->GetPosition().GetY(), player->GetPosition().GetZ());
				Console::PrintLn("ID: %d", *player->GetTeam());
				Console::PrintLn("Range: %f", *player->GetRange());
				Console::PrintLn("Champion Name: %s", player->GetChampionName());
				Console::PrintLn("Name: %s", player->GetName());
				Console::PrintLn("Bounding Radius: %f", player->GetBoundingRadius());
				Console::PrintLn("Health: %f", *player->GetHealth());
				Console::PrintLn("MaxHealth: %f", *player->GetMaxHealth());
				Console::PrintLn("Mana: %f", *player->GetMana());
				Console::PrintLn("MaxMana: %f", *player->GetMaxMana());
				*/

			}
		}
	}

	HMODULE Core::get_hModule() const
	{
		return this->hModule;
	}

	void Core::set_hModule(HMODULE h)
	{
		this->hModule = h;
	}

	Detour* Core::get_DetourInstance()
	{
		static auto instance = new Detour();
		return instance;
	}

	bool Core::ApplyHooks() const
	{
		VERIFY_HOOK(RiotX3D::AppyHooks, "RiotX3D");
		//VERIFY_HOOK(AttackableUnit::ApplyHooks, "AttackableUnit");
		//VERIFY_HOOK( CharacterDataStack::ApplyHooks, "CharacterDataStack" );
		//VERIFY_HOOK( r3dCamera::ApplyHooks, "r3dCamera" );
		//VERIFY_HOOK( PacketLayer::ApplyHooks, "PacketLayer");
		//VERIFY_HOOK( CRepl32Info::ApplyHooks, "CRepl32Info");
		//VERIFY_HOOK( RiotRadsIO::ApplyHooks, "RiotRadsIO" );

		return true;
	}
}