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

tyga::Vector3 Lerp(tyga::Vector3 Start, tyga::Vector3 End, float s)
{
	return (Start * (1 - s) + End * s);
}

const float LerpFloat(float Start, float End, float s)
{
	return (Start * (1 - s) + End * s);
}

float Clamp(float Time, float Start, float Stop)
{
	if (Time < Start)
	{
		Time = Start;
	}

	if (Time > Stop)
	{
		Time = Stop;
	}

	return Time;
}

float LinearStep(float min, float max, float x)
{
	return Clamp(0, 1, (x - min) / (max - min));
}

float SmoothStep(float min, float max, float x)
{
	x = LinearStep(min, max, x);
	return 3 * x * x - 2 * x * x * x;
}

tyga::Vector3 BezierCurve(float StartTime, float EndTime, float Time, tyga::Vector3 p0, tyga::Vector3 p1, tyga::Vector3 p2, tyga::Vector3 p3)
{
	const float s = JoshAinley::LinearStep(StartTime, EndTime, Time);

	const float b0 = (1 - s) * (1 - s) * (1 - s);
	const float b1 = 3 * s *  (1 - s) * (1 - s);
	const float b2 = 3 * s * s * (1 - s);
	const float b3 = s * s * s;

	tyga::Vector3 pos = p0 * b0 + p1 * b1 + p2 * b2 + p3 * b3;

	return pos;
}

tyga::Vector3 Euler(tyga::Vector3 position, tyga::Vector3 velocity, float deltaTime)
{
	return position + deltaTime * velocity;
}

tyga::Matrix4x4 frenet(	const tyga::Vector3& pos,
						const tyga::Vector3& dir,
						const tyga::Vector3& up)
{
	// W, U, V need to be converted into unit vectors properly so the function doesnt fail
	const tyga::Vector3 W = tyga::unit(dir);
	const tyga::Vector3 U = tyga::cross(up, W);
	const tyga::Vector3 V = tyga::cross(U, W);

	return tyga::Matrix4x4( U.x, U.y, U.z, 0,
							V.x, V.y, V.z, 0,
							W.x, W.y, W.z, 0,
							pos.x, pos.y, pos.z, 1);
}

}

float DistanceTravelled(float Speed, float DeltaTime)
{
	return (Speed * DeltaTime);
}

