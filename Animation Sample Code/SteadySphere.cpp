#include "SteadySphere.hpp"
#include "MyUtils.hpp"

#include <tyga/BasicWorldClock.hpp>
#include <tyga/Math.hpp>

void SteadySphere::
actorDidEnterWorld(std::shared_ptr<tyga::Actor> root_actor)
{
    auto graphics = tyga::GraphicsCentre::defaultCentre();

    auto model = graphics->newModel();
    model->material = graphics->newMaterial();
    model->material->colour = tyga::Vector3(1.f, 0.f, 0.f);
    model->mesh = graphics->newMeshWithIdentifier("sphere");
    root_actor->attachComponent(model);
}

void SteadySphere::
actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor)
{
}

void SteadySphere::
actorClockTick(std::shared_ptr<tyga::Actor> actor)
{
    const float time = tyga::BasicWorldClock::CurrentTime();
    const float delta_time = tyga::BasicWorldClock::CurrentTickInterval();
	
	//the values used for the translation of the sphere
	float x{ -3 };
	float y{ 3 };
	float z{ 0.5};

	tyga::Matrix4x4 a = JoshAinley::translate(x, y, z);
	auto xform = tyga::Matrix4x4(a);

    actor->setTransformation(xform);
}
