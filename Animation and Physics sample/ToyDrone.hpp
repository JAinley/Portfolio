#pragma once

#include "MyPhysicsCentre.hpp"

#include <tyga/ActorDelegate.hpp>

class ToyDrone : public tyga::ActorDelegate
{
public:

    void
    reset(tyga::Vector3 position, float mass);

    void
    applyForce(tyga::Vector3 force);

    void
    trigger();

private:

    virtual void
    actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorClockTick(std::shared_ptr<tyga::Actor> actor) override;

    std::shared_ptr<PhysicsSphere> physics_model_;

};
