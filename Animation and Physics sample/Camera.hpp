#pragma once

#include <tyga/ActorDelegate.hpp>

class Camera : public tyga::ActorDelegate
{
public:

    void
    setHeadingAngle(float radians);

    void
    setHeadingSpeed(float speed);

    void
    setPanDistance(float distance);

    void
    setPanSpeed(float speed);

private:

    virtual void
    actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorClockTick(std::shared_ptr<tyga::Actor> actor) override;

    std::shared_ptr<tyga::Actor> camera_actor_;
    float heading_angle_{ 2 };
    float heading_speed_{ 0 };
    float pan_distance_{ 5 };
    float pan_speed_{ 0 };
};
