#include "IndignantCylinder.hpp"
#include "MyUtils.hpp"

#include <tyga/BasicWorldClock.hpp>
#include <tyga/Math.hpp>

void IndignantCylinder::
actorDidEnterWorld(std::shared_ptr<tyga::Actor> root_actor)
{
    auto graphics = tyga::GraphicsCentre::defaultCentre();

    auto model = graphics->newModel();
    model->material = graphics->newMaterial();
	model->material->colour = tyga::Vector3(1.f, 1.f, 0.f);
    model->mesh = graphics->newMeshWithIdentifier("cylinder");
    root_actor->attachComponent(model);
}

void IndignantCylinder::
actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor)
{
}

void IndignantCylinder::
actorClockTick(std::shared_ptr<tyga::Actor> actor)
{
    const float time = tyga::BasicWorldClock::CurrentTime();
    const float delta_time = tyga::BasicWorldClock::CurrentTickInterval();

	const float x = JoshAinley::oscillate(1.5f, 1.0f, 0.2f, time);
	auto xform2 = JoshAinley::scale(x);
	auto xform = JoshAinley::translate(0, 0, 0);

    actor->setTransformation(xform * xform2);
}
