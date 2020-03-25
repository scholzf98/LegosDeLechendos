#include "Renderer.h"
#include "r3dRenderer.h"
#include "ObjectManager.h"

namespace Scholzf
{
	bool Renderer::DrawMessage(LPD3DXFONT font, unsigned int x, unsigned int y, int alpha, unsigned char r, unsigned char g, unsigned char b, LPCSTR Message)
	{	// Create a colour for the text
		D3DCOLOR fontColor = D3DCOLOR_ARGB(alpha, r, g, b);
		RECT rct; //Font
		rct.left = x;
		rct.right = 1680;
		rct.top = y;
		rct.bottom = rct.top + 200;
		font->DrawTextA(NULL, Message, -1, &rct, 0, fontColor);
		return true;
	}
}