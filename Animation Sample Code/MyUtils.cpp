#include "MyUtils.hpp"

/*
 * Tutorial: use this source and its associated header file to declare
 *           and define your own helper functions.
 */

namespace JoshAinley
{

tyga::Matrix4x4 translate(float x, float y, float z)
{
    return tyga::Matrix4x4(       1,       0,       0,       0,
                                  0,       1,       0,       0,
                                  0,       0,       1,       0,
                                  x,       y,       z,       1);
}

tyga::Matrix4x4 rotateZ(float angle)
{
	const float c = std::cos(angle);
	const float s = std::sin(angle);
	return tyga::Matrix4x4(	c, s, 0, 0,
							-s, c, 0, 0,
							0, 0, 1, 0,
							0, 0, 0, 1);

}

tyga::Matrix4x4 rotateX(float angle)
{
	const float c = std::cos(angle);
	const float s = std::sin(angle);
	return tyga::Matrix4x4( 1, 0, 0, 0,
							0, c, s, 0,
							0, -s, c, 0,
							0, 0, 0, 1);

}

tyga::Matrix4x4 rotateY(float angle)
{
	const float c = std::cos(angle);
	const float s = std::sin(angle);
	return tyga::Matrix4x4( c, 0, -s, 0,
							0, 1, 0, 0,
							s, 0, c, 0,
							0, 0, 0, 1);

}
float continous(float speed, float time)
{
	return speed * time;
}
float oscillate(float intial, float a, float omega, float t)
{
	float x = intial + a * sin(M_2_PI * t + omega);
	return std::abs(x);
}

tyga::Matrix4x4 scale(float x)
{
	float a = x;
	return tyga::Matrix4x4( a, 0, 0, 0,
							0, a, 0, 0,
							0, 0, a, 0,
							0, 0, 0, 1);
}

}

