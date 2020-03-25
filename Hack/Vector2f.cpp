#include "Vector2f.h"

using namespace std;

namespace Scholzf
{
	Vector2f::Vector2f()
	{

	}

	Vector2f::Vector2f(float xx, float yy) : X(xx), Y(yy) {}

	Vector2f::operator float* ()
	{
		return &X;
	}

	float Vector2f::GetX() const
	{
		return X;
	}

	float Vector2f::GetY() const
	{
		return Y;
	}

}
