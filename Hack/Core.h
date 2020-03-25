#pragma once
#include "Utils.h"

#define VERIFY_HOOK(HOOK, NAME) if (!HOOK ()) { return false; }

namespace Scholzf
{

	class Detour;
	class AIHeroClient;

	class Core
	{
		HMODULE hModule;
		bool ApplyHooks() const;
	public:
		explicit Core(HMODULE h_module);
		~Core();

		void DisplayWelcomeMessage() const;

		HMODULE get_hModule() const;
		void set_hModule(HMODULE h);

		void main(AIHeroClient* player) const;

		/*
		 * static
		*/
		static int mainModule;

		template <typename T>
		static T GetAddress(DWORD virtualAddr);

		static Detour* get_DetourInstance();
	};

	template <typename T>
	T Core::GetAddress(DWORD virtualAddr)
	{
		return static_cast<T>(mainModule) + virtualAddr;
	}
}