// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "pch.h"
#include <Windows.h>
#include "Console.h"
#include "Core.h"
#include "Utils.h"
using namespace Scholzf;

DWORD WINAPI Loop(PVOID parameters)
{
	Console::Create();

	Core::mainModule = reinterpret_cast<int>(GetModuleHandle(nullptr));

	auto _core = new Core(GetModuleHandle(nullptr));

	return true;
}

BOOL WINAPI DllMain(HINSTANCE dllInstance, DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		// Optimize our cheat by ignoring DLL_THREAD_ATTACH and DLL_THREAD_DETACH
		CreateThread(NULL, 0, &Loop, NULL, 0, NULL);

	}

	if (reason == DLL_PROCESS_DETACH)
	{
		SuspendThread(dllInstance);
	}

	// Return success
	return true;
}

/*

#include <conio.h>
#include <stdio.h>
#include <Windows.h>
using namespace Scholzf;

DWORD WINAPI MainConsole(LPVOID lpParam)
{
	
	AllocConsole();
	HWND hWnd = GetConsoleWindow();
	freopen("CONOUT$", "w", stdout);
	//SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOSIZE | SWP_SHOWWINDOW);
	SetConsoleTitle("test");
	Sleep(2000);
	printf_s("----------------------------------\n");
	printf_s("TEST TEST TEST TEST TEST TEST TEST\n");
	printf_s("----------------------------------\n");
	fflush(NULL);
	system("PAUSE");
	fflush(NULL);
	printf_s("\nTEST\tTEST\nTEST");


	Console::Create();
	return 1;
}

BOOL APIENTRY DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		CreateThread(NULL, 0, &MainConsole, NULL, 0, NULL);
	}

	return TRUE;
}
	*/