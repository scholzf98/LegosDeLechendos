#pragma once
#include "MemoryScanner.h"

namespace Scholzf
{

	bool MemoryScanner::Mask(const BYTE* pData, const BYTE* bMask, const char* szMask)
	{
		for (; *szMask; ++szMask, ++pData, ++bMask)
			if (*szMask == 'x' && *pData != *bMask)
				return false;
		return (*szMask) == NULL;
	}

	DWORD MemoryScanner::FindPattern(DWORD dwAddress, DWORD dwLen, BYTE* bMask, const char* szMask)
	{
		for (DWORD i = 0; i < dwLen; i++)
			if (Mask((BYTE*)(dwAddress + i), bMask, szMask))
				return (DWORD)(dwAddress + i);
		return 0;
	}

	bool MemoryScanner::GetKeyPressed(int vKey)
	{
		return GetAsyncKeyState(vKey) & 1 ? true : false;
	}

	DWORD MemoryScanner::FindDevice(DWORD Len)
	{
		DWORD dwObjBase = 0;

		dwObjBase = (DWORD)LoadLibrary("d3d9.dll");
		while (dwObjBase++ < dwObjBase + Len)
		{
			if ((*(WORD*)(dwObjBase + 0x00)) == 0x06C7
				&& (*(WORD*)(dwObjBase + 0x06)) == 0x8689
				&& (*(WORD*)(dwObjBase + 0x0C)) == 0x8689
				) {
				dwObjBase += 2; break;
			}
		}
		return(dwObjBase);
	}

	DWORD MemoryScanner::GetDeviceAddress(int VTableIndex)
	{
		PDWORD VTable;
		*(DWORD*)&VTable = *(DWORD*)FindDevice(0x128000);
		return VTable[VTableIndex];
	}

}