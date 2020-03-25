#pragma once
#include <Windows.h>

namespace Scholzf
{

	class
		Console
	{
	public:
		static void Create();
		static void PrintLn(const char* format, ...);
		static void Show();
		static void Hide();

		static HWND GetHandle();
	};
}