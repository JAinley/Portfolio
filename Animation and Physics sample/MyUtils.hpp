#pragma once

#include <tyga/Math.hpp>

/*
 * Tutorial: use this header and its associated source file to declare
 *           and define your own helper functions.
 */

namespace JoshAinley
{

/**
 * Makes a translation transformation matrix.
 *
 * @param x The amount of X translation.
 * @param y The amount of Y translation.
 * @param z The amount of Z translation.
 * @return  A 4x4 transformation matrix for use with row-vectors.
 */
tyga::Matrix4x4 translate(float x, float y, float z);
tyga::Matrix4x4 rotateZ(float angle);
tyga::Matrix4x4 rotateX(float angle);
tyga::Matrix4x4 rotateY(float angle);
float continous(float speed, float time);
float oscillate(float intial, float a, float omega, float t);
tyga::Matrix4x4 scale(float x);

tyga::Vector3 Lerp(tyga::Vector3 Start, tyga::Vector3 End, float s);
const float LerpFloat(float Start, float End, float s);
float Clamp(float Time, float Start, float Stop);
float LinearStep(float min, float max, float x);
float SmoothStep(float min, float max, float x);
tyga::Vector3 BezierCurve(float StartTime, float EndTime, float Time, tyga::Vector3 p0, tyga::Vector3 p1, tyga::Vector3 p2, tyga::Vector3 p3 );

tyga::Vector3 Euler(tyga::Vector3 position, tyga::Vector3 velocity, float deltaTime);
}
