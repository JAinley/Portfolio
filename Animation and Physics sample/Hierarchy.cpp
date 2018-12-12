#include "Hierarchy.h"



Hierarchy::Hierarchy()
{
}


Hierarchy::~Hierarchy()
{
}


void Hierarchy::AddChild(std::shared_ptr<tyga::Actor> actor_ , tyga::Matrix4x4 localxform)
{
	actor = actor_;
	localXform = localxform;
}

void Hierarchy::setPose(tyga::Matrix4x4 transformation)
{
	tyga::Matrix4x4 newtransform = localXform * transformation;

	actor->setTransformation(newtransform);


}