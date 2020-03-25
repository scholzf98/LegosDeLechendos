#pragma once
#include <math.h>
#include <stdlib.h>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace Scholzf
{
	class Vector3f
	{
	protected:
		float X, Y, Z;
	public:
		Vector3f();
		Vector3f(float xx, float yy, float zz);

		Vector3f SwitchYZ() const;
		bool IsValid() const;
		operator float* ();

		float GetX() const;
		float GetY() const;
		float GetZ() const;
		float DistanceTo(const Vector3f& v) const;
		D3DXVECTOR3 To3D() const;
		Vector3f Randomize();
	};
	
};
