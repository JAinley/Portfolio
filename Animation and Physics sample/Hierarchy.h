
#include <tyga/Actor.hpp>
#include <tyga/BasicWorldClock.hpp>
#include <tyga/Math.hpp>
#include <tyga/ActorWorld.hpp>
#include <tyga/GraphicsCentre.hpp>

#pragma once
class Hierarchy
{
public:
	Hierarchy();
	~Hierarchy();

	void AddChild(std::shared_ptr<tyga::Actor> actor_ , tyga::Matrix4x4 xform);
	void setPose(tyga::Matrix4x4 parentxform);

private:
	tyga::Matrix4x4 localXform{ 1, 0, 0, 0,
								0, 1, 0, 0,
								0, 0, 1, 0,
								0, 0, 0, 1 };

	std::shared_ptr<tyga::Actor> actor;
	std::vector<std::shared_ptr<tyga::Actor>> child;
	Hierarchy *parent;

};

