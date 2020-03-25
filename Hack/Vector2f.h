#pragma once
#include <math.h>
#include <stdlib.h>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace Scholzf
{
	class Vector2f
	{
	protected:
		float X, Y, Z;
	public:
		Vector2f();
		Vector2f(float xx, float yy);

		operator float* ();

		float GetX() const;
		float GetY() const;
	};

};
