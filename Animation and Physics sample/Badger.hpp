#pragma once

#include <tyga/ActorDelegate.hpp>

#include <vector>


class Badger : public tyga::ActorDelegate
{
public:

    /**
     * An actor translated and scaled to the bounding box of the Badger.
     */
    std::shared_ptr<tyga::Actor>
    boundsActor();
	//
	//void setSpeed(float speed);

	//void SetTurn(float TurnAngle);


private:

    virtual void
    actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorClockTick(std::shared_ptr<tyga::Actor> actor) override;

	float speed_{ 0.f };
	float turnAngle_{ 0.f };
	float DeltaHeadingAngle{ 0.f };
	float DeltaWheelSpin;

	float loopTime = 0;

	std::shared_ptr<tyga::Actor> chassis_actor_;
	std::shared_ptr<tyga::Actor> handlebar_actor_;
	std::shared_ptr<tyga::Actor> luggage_rack_actor_;
	std::vector<std::shared_ptr<tyga::Actor>> wheel_actor_;

	std::shared_ptr<tyga::Actor> torso_actor_;
	std::shared_ptr<tyga::Actor> pelvis_actor_;
	std::shared_ptr<tyga::Actor> helmet_actor_;

	std::shared_ptr<tyga::Actor> arm_left_actor_;
	std::shared_ptr<tyga::Actor> forearm_left_actor_;
	std::shared_ptr<tyga::Actor> hand_left_actor_;

	std::shared_ptr<tyga::Actor> arm_right_actor_;
	std::shared_ptr<tyga::Actor> forearm_right_actor_;
	std::shared_ptr<tyga::Actor> hand_right_actor_;

	std::shared_ptr<tyga::Actor> leg_left_actor_;
	std::shared_ptr<tyga::Actor> shin_left_actor_;
	std::shared_ptr<tyga::Actor> foot_left_actor_;

	std::shared_ptr<tyga::Actor> leg_right_actor_;
	std::shared_ptr<tyga::Actor> shin_right_actor_;
	std::shared_ptr<tyga::Actor> foot_right_actor_;

	std::shared_ptr<tyga::Actor> ToyParticles;












    std::shared_ptr<tyga::Actor> physics_actor_;
};
