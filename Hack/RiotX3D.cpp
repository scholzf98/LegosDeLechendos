#pragma once
#include "Detour.hpp"
#include "MemoryScanner.h"
#include "RiotX3D.h"
#include "Vector3f.h"
#include "ObjectManager.h"
#include "AIHeroClient.h"
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include "Console.h"
#include "Renderer.h"

namespace Scholzf
{

	MAKE_HOOK<convention_type::stdcall_t, HRESULT, LPDIRECT3DDEVICE9> EndScene;
	MAKE_HOOK<convention_type::stdcall_t, HRESULT, LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS*> ResetScene;

	MAKE_CALL<static_cast<DWORD>(Offsets::r3dRenderer::DrawCircularRangeIndicator), convention_type::cdecl_t, void*, Vector3f*/*pos*/, float /*radius*/, int*/*color*/, int/**/, float /*0*/, int /*0*/, float /*Default 1*/ >r3dDrawCircle;
	MAKE_CALL<static_cast<DWORD>(Offsets::r3dRenderer::W2S), convention_type::cdecl_t, bool*, Vector3f*, Vector3f*> World2ScreenFunc;

	LPD3DXFONT m_font = NULL;
	AIHeroClient* player;
	int pcolor = 0x000099;

	bool isPartOf(const std::string& word, const std::string& sentence) {
		return sentence.find(word)    // this returns the index of the first instance
									  // word
			!= std::string::npos;  // which will take this value if it's not found
	}

	bool RiotX3D::AppyHooks()
	{
		HMODULE hModule = NULL;

		while (!hModule)
		{
			hModule = GetModuleHandle("d3d9.dll");
			Sleep(100);
		}

		DWORD* VTableStart = 0;
		DWORD dwVTablePattern = MemoryScanner::FindPattern((DWORD)hModule, 0x128000, (PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86", "xx????xx????xx");
		memcpy(&VTableStart, (void*)(dwVTablePattern + 2), 4);

		DWORD dwEndScene = (DWORD)VTableStart[42];
		DWORD dwResetScene = (DWORD)VTableStart[16];

		EndScene.Apply((dwEndScene), [](LPDIRECT3DDEVICE9 pDevice) -> HRESULT
			{
				D3DXCreateFont(pDevice, 17, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Times New Roman"), &m_font);

				Renderer::DrawMessage(m_font, 40, 40, 255, 255, 0, 255, "scholzCore");

				player = ObjectManager::GetPlayer();

				auto obj = ObjectManager::GetFirstObject();


				while (obj)
				{

					obj = ObjectManager::GetNextObject(obj);
				}

				Vector3f out;
				auto b = World2ScreenFunc.Call(&player->GetPosition(), &out);
				Renderer::DrawMessage(m_font, out.GetX(), out.GetY(), 255, 255, 51, 51, player->GetName());

				r3dDrawCircle.Call(&player->GetPosition(), *player->GetRange() + player->GetBoundingRadius(), &pcolor, 0, 0, 0, 1);

				auto returnValue = EndScene.CallOriginal(pDevice);
				return returnValue;
			});

		ResetScene.Apply((dwResetScene), [](LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* presentationParameters) -> HRESULT
			{
				pDevice->Reset(presentationParameters);

				auto returnValue = ResetScene.CallOriginal(pDevice, presentationParameters);
				return returnValue;
			});

		return EndScene.IsApplied() && ResetScene.IsApplied();
	}
}