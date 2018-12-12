#pragma once

#include <algorithm>
class cRectangle
{
public:
	//sets a default constructor
	cRectangle() = default;
	//sets the rectangle sides
	cRectangle(int l, int r, int t, int b) : left(l), right(r), top(t), bottom(b) {};
	//rectangle sides are set to 0
	int left{ 0 }, right{ 0 }, top{ 0 }, bottom{ 0 };

	unsigned int GetWidth() const { return right - left; }
	unsigned int GetHeight() const { return bottom - top; }

	//checks if the one rectangle contains another
	bool cRectangle::Contains(const cRectangle &other)
	{
		return !(left >= other.left && top >= other.top && right <= other.right && bottom <= other.bottom);
	}

	bool cRectangle::intersect(const cRectangle &other) {
		//intersect top left
		if ((right > other.left && right < other.right)
			&& (bottom >= other.top && bottom <= other.bottom)) {
			return true;
		}
		//intersect top right
		else if ((left < other.right && right > other.right)
			&& (bottom >= other.top && bottom <= other.bottom)) {
			return true;
		}
		//intersect bottom left
		else if ((right > other.left && right < other.right)
			&& (top <= other.bottom && top >= other.top)) {
			return true;
		}
		//intersect bottom right
		else if ((left < other.right && right > other.right)
			&& (top <= other.bottom && top >= other.top)) {
			return true;
		}
		else
		{
			return false;
		}
	}

	//checks if one rectangle is completely out of another
	bool OutsideOf(const cRectangle &other)
	{
		return (left > other.right || top > other.bottom || right < other.left || bottom < other.top);
	}

	//clips one rectangle to another
	void ClipTo(const cRectangle &other)
	{
		if (left < other.left) left = other.left;
		if (top < other.top) top = other.top;
		if (right > other.right) right = other.right;
		if (bottom > other.bottom) bottom = other.bottom;

	}

	//moves the rectangle
	void Translate(int dx, int dy)
	{
		left += dx;
		top += dy;
		bottom += dy;
		right += dx;
	}
};

