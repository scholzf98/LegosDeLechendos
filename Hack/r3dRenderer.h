#pragma once
#include"Macros.h"
#include "Offsets.h"
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace Scholzf
{
	class r3dRenderer
	{
	public:
		MAKE_GET(ProjectionMatrix, D3DXMATRIX, Offsets::r3dRendererStruct::Projection);
		MAKE_GET(ViewMatrix, D3DXMATRIX, Offsets::r3dRendererStruct::View);
		MAKE_GET(ScreenWidth, int, Offsets::r3dRendererStruct::ClientWidth);
		MAKE_GET(ScreenHeight, int, Offsets::r3dRendererStruct::ClientHeight);

	private:

	};
}
