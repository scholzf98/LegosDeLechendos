#pragma once
#ifndef __MemoryScanner
#define __MemoryScanner

#include "pch.h"

namespace Scholzf
{

	class MemoryScanner
	{
	public:
		static bool Mask(const BYTE* pData, const BYTE* bMask, const char* szMask);
		static DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE* bMask, const char* szMask);
		static bool GetKeyPressed(int vKey);
		static DWORD FindDevice(DWORD Len);
		static DWORD GetDeviceAddress(int VTableIndex);
	};

#endif
}