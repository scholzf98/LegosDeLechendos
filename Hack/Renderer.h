#pragma once

#include "Vector3f.h"
#include "Vector2f.h"
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace Scholzf
{
	class Renderer
	{
	public:
		static bool DrawMessage(LPD3DXFONT font, unsigned int x, unsigned int y, int alpha, unsigned char r, unsigned char g, unsigned char b, LPCSTR Message);
		static Vector2f World2Screen(Vector3f* input, Vector2f* output);
	};
}
