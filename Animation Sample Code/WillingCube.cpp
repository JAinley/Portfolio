#include "WillingCube.hpp"
#include "MyUtils.hpp"

#include <tyga/BasicWorldClock.hpp>
#include <tyga/Math.hpp>

void WillingCube::
actorDidEnterWorld(std::shared_ptr<tyga::Actor> root_actor)
{
    auto graphics = tyga::GraphicsCentre::defaultCentre();

    auto model = graphics->newModel();
    model->material = graphics->newMaterial();
	model->material->colour = tyga::Vector3(0.f, 0.f, 1.f);
    model->mesh = graphics->newMeshWithIdentifier("cube");
    root_actor->attachComponent(model);
}

void WillingCube::
actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor)
{
}

void WillingCube::
actorClockTick(std::shared_ptr<tyga::Actor> actor)
{


	const float time = tyga::BasicWorldClock::CurrentTime();
    const float delta_time = tyga::BasicWorldClock::CurrentTickInterval();

	const float rate = JoshAinley::continous(0.25f, time);
	tyga::Matrix4x4 xform = JoshAinley::rotateZ(rate);
	tyga::Matrix4x4 xform1 = JoshAinley::translate(3, -3, 1);
	

	tyga::Matrix4x4 xform2 = xform*xform1;
	// for spinning use new_xform in brackets
	//auto new_xform = xform2 * actor->Transformation();
	actor->setTransformation(xform2);
	
}
