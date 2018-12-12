#include "HopefulCone.hpp"
#include "MyUtils.hpp"

#include <tyga/BasicWorldClock.hpp>
#include <tyga/Math.hpp>

void HopefulCone::
actorDidEnterWorld(std::shared_ptr<tyga::Actor> root_actor)
{
    auto graphics = tyga::GraphicsCentre::defaultCentre();

    auto model = graphics->newModel();
    model->material = graphics->newMaterial();
	model->material->colour = tyga::Vector3(0.f, 1.f, 0.f);
    model->mesh = graphics->newMeshWithIdentifier("cone");
    root_actor->attachComponent(model);
}

void HopefulCone::
actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor)
{
}

void HopefulCone::
actorClockTick(std::shared_ptr<tyga::Actor> actor)
{

	const float time = tyga::BasicWorldClock::CurrentTime();
	const float delta_time = tyga::BasicWorldClock::CurrentTickInterval();

	//const float rate = 0.5 * delta_time;
	//const float angle = 0.25;
	const float angle = JoshAinley::continous(0.5f, time);

	tyga::Matrix4x4 xformCR = JoshAinley::rotateZ(angle);
	tyga::Matrix4x4 xformCT = JoshAinley::translate(3, -3, 3);

	tyga::Matrix4x4 xform = xformCT * xformCR;

    actor->setTransformation(xform);
}
