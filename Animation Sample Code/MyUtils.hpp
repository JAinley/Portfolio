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
float continous(float speed, float time);
float oscillate(float intial, float a, float omega, float t);
tyga::Matrix4x4 scale(float x);

}
