#include "ToyDrone.hpp"
#include "MyUtils.hpp"

#include <tyga/Actor.hpp>
#include <tyga/BasicWorldClock.hpp>
#include <tyga/Math.hpp>
#include <tyga/ActorWorld.hpp>
#include <tyga/GraphicsCentre.hpp>
#include <tyga/Log.hpp>

#include <cassert>


void ToyDrone::
reset(tyga::Vector3 position, float mass)
{
    // NB: this method should not need changing

    const auto& p = position;
    auto xform = tyga::Matrix4x4(    1,   0,   0,  0,
                                     0,   1,   0,  0,
                                     0,   0,   1,  0,
                                   p.x, p.y, p.z,  1);
    Actor()->setTransformation(xform);
    physics_model_->mass = mass;
}

void ToyDrone::
applyForce(tyga::Vector3 force)
{
    // NB: this method should not need changing

    physics_model_->force += force;
}

void ToyDrone::
trigger()
{
    // NB: this method should not be changed

    assert(false && "ToyDrone::trigger method should not be used");
    tyga::debugLog("ToyDrone::trigger: toy should explode now");
}

void ToyDrone::
actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor)
{
    auto world = tyga::ActorWorld::defaultWorld();
    auto graphics = tyga::GraphicsCentre::defaultCentre();
    auto physics = MyPhysicsCentre::defaultCentre();

    auto graphics_model = graphics->newModel();
    graphics_model->material = graphics->newMaterial();
    graphics_model->material->colour = tyga::Vector3(1, 0.33f, 0);
    graphics_model->mesh = graphics->newMeshWithIdentifier("sphere");
    graphics_model->xform = tyga::Matrix4x4( 0.5f,    0,    0,   0,
                                                0, 0.5f,    0,   0,
                                                0,    0, 0.5f,   0,
                                                0,    0,    0,   1);

    auto physics_model = physics->newSphere();
    physics_model->radius = 0.25f;
    physics_model->mass = 1.f;
    physics_model_ = physics_model;

	// Newtons law of gravity:
	//  F = Gavity(6.67x10-11)


    actor->attachComponent(graphics_model);
    actor->attachComponent(physics_model);
    world->addActor(actor);
}

void ToyDrone::
actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor)
{
}

void ToyDrone::
actorClockTick(std::shared_ptr<tyga::Actor> actor)
{
}
