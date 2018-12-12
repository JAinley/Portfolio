#include "Badger.hpp"
#include "MyUtils.hpp"

#include <tyga/Actor.hpp>
#include <tyga/BasicWorldClock.hpp>
#include <tyga/Math.hpp>
#include <tyga/ActorWorld.hpp>
#include <tyga/GraphicsCentre.hpp>
#include "Hierarchy.h"
#include "ToyParticles.hpp"

#include <iostream>


std::shared_ptr<tyga::Actor> Badger::
boundsActor()
{
    return physics_actor_;
}

void Badger::
actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor)
{
    auto world = tyga::ActorWorld::defaultWorld();
    auto graphics = tyga::GraphicsCentre::defaultCentre();

    physics_actor_ = std::make_shared<tyga::Actor>();
    world->addActor(physics_actor_);
	

	
	//this part creates all the models and materials for all parts for the badger and the bloke and loads echa part from the tcf file
	


	//chassis component
	auto chassis_material = graphics->newMaterial();
	chassis_material->colour = tyga::Vector3(1.f, 0.2f, 0.2f);
	auto chassis_mesh = graphics->newMeshWithIdentifier("badger.tcf/chassis");
	auto chassis_model = graphics->newModel();
	chassis_model->material = chassis_material;
	chassis_model->mesh = chassis_mesh;
	chassis_actor_ = std::make_shared<tyga::Actor>();
	chassis_actor_->attachComponent(chassis_model);
	world->addActor(chassis_actor_);

	//handlebar component
	auto handlebar_material = graphics->newMaterial();
	handlebar_material->colour = tyga::Vector3(0.f, 0.2f, 0.6f);
	auto handlebar_mesh = graphics->newMeshWithIdentifier("badger.tcf/handlebar");
	auto handlebar_model = graphics->newModel();
	handlebar_model->material = handlebar_material;
	handlebar_model->mesh = handlebar_mesh;
	handlebar_actor_ = std::make_shared<tyga::Actor>();
	handlebar_actor_->attachComponent(handlebar_model);
	world->addActor(handlebar_actor_);

	//luggage rack component
	auto luggage_rack_material = graphics->newMaterial();
	luggage_rack_material->colour = tyga::Vector3(0.f, 0.7f, 0.f);
	auto luggage_rack_mesh = graphics->newMeshWithIdentifier("badger.tcf/luggage_rack");
	auto luggage_rack_model = graphics->newModel();
	luggage_rack_model->material = luggage_rack_material;
	luggage_rack_model->mesh = luggage_rack_mesh;
	luggage_rack_actor_ = std::make_shared<tyga::Actor>();
	luggage_rack_actor_->attachComponent(luggage_rack_model);
	world->addActor(luggage_rack_actor_);

	//creates the weheels in an array
	wheel_actor_.resize(4);

	for (int i = 0; i < 4; i++)
	{
		auto wheel_material = graphics->newMaterial();
		wheel_material->colour = tyga::Vector3(1, 1, 1);
		auto wheel_mesh = graphics->newMeshWithIdentifier("badger.tcf/wheel");
		auto wheel_model = graphics->newModel();
		wheel_model->material = wheel_material;
		wheel_model->mesh = wheel_mesh;
		wheel_actor_[i] = std::make_shared<tyga::Actor>();
		wheel_actor_[i]->attachComponent(wheel_model);
		world->addActor(wheel_actor_[i]);
	}


	//blokes torso component
	auto torso_material = graphics->newMaterial();
	torso_material->colour = tyga::Vector3(0.f, 1.f, 0.f);
	auto torso_mesh = graphics->newMeshWithIdentifier("bloke.tcf/torso");
	auto torso_model = graphics->newModel();
	torso_model->material = torso_material;
	torso_model->mesh = torso_mesh;
	torso_actor_ = std::make_shared<tyga::Actor>();
	torso_actor_->attachComponent(torso_model);
	world->addActor(torso_actor_);

	//blokes helmet component
	auto helmet_material = graphics->newMaterial();
	helmet_material->colour = tyga::Vector3(0.f, 1.f, 0.f);
	auto helmet_mesh = graphics->newMeshWithIdentifier("bloke.tcf/helmet");
	auto helmet_model = graphics->newModel();
	helmet_model->material = helmet_material;
	helmet_model->mesh = helmet_mesh;
	helmet_actor_ = std::make_shared<tyga::Actor>();
	helmet_actor_->attachComponent(helmet_model);
	world->addActor(helmet_actor_);

	//blokes pelvis component
	auto pelvis_material = graphics->newMaterial();
	pelvis_material->colour = tyga::Vector3(0.f, 1.f, 0.f);
	auto pelvis_mesh = graphics->newMeshWithIdentifier("bloke.tcf/pelvis");
	auto pelvis_model = graphics->newModel();
	pelvis_model->material = pelvis_material;
	pelvis_model->mesh = pelvis_mesh;
	pelvis_actor_ = std::make_shared<tyga::Actor>();
	pelvis_actor_->attachComponent(pelvis_model);
	world->addActor(pelvis_actor_);


	//blokes left arm
	auto arm_left_material = graphics->newMaterial();
	arm_left_material->colour = tyga::Vector3(0.f, 1.f, 0.f);
	auto arm_left_mesh = graphics->newMeshWithIdentifier("bloke.tcf/arm_left");
	auto arm_left_model = graphics->newModel();
	arm_left_model->material = arm_left_material;
	arm_left_model->mesh = arm_left_mesh;
	arm_left_actor_ = std::make_shared<tyga::Actor>();
	arm_left_actor_->attachComponent(arm_left_model);
	world->addActor(arm_left_actor_);


	//blokes left forearm
	auto forearm_left_material = graphics->newMaterial();
	forearm_left_material->colour = tyga::Vector3(0.f, 1.f, 0.f);
	auto forearm_left_mesh = graphics->newMeshWithIdentifier("bloke.tcf/forearm_left");
	auto forearm_left_model = graphics->newModel();
	forearm_left_model->material = forearm_left_material;
	forearm_left_model->mesh = forearm_left_mesh;
	forearm_left_actor_ = std::make_shared<tyga::Actor>();
	forearm_left_actor_->attachComponent(forearm_left_model);
	world->addActor(forearm_left_actor_);


	//blokes left hand
	auto hand_left_material = graphics->newMaterial();
	hand_left_material->colour = tyga::Vector3(0.f, 1.f, 0.f);
	auto hand_left_mesh = graphics->newMeshWithIdentifier("bloke.tcf/hand_left");
	auto hand_left_model = graphics->newModel();
	hand_left_model->material = hand_left_material;
	hand_left_model->mesh = hand_left_mesh;
	hand_left_actor_ = std::make_shared<tyga::Actor>();
	hand_left_actor_->attachComponent(hand_left_model);
	world->addActor(hand_left_actor_);


	//blokes right arm
	auto arm_right_material = graphics->newMaterial();
	arm_right_material->colour = tyga::Vector3(0.f, 1.f, 0.f);
	auto arm_right_mesh = graphics->newMeshWithIdentifier("bloke.tcf/arm_right");
	auto arm_right_model = graphics->newModel();
	arm_right_model->material = arm_right_material;
	arm_right_model->mesh = arm_right_mesh;
	arm_right_actor_ = std::make_shared<tyga::Actor>();
	arm_left_actor_->attachComponent(arm_right_model);
	world->addActor(arm_right_actor_);


	//blokes right forearm
	auto forearm_right_material = graphics->newMaterial();
	forearm_right_material->colour = tyga::Vector3(0.f, 1.f, 0.f);
	auto forearm_right_mesh = graphics->newMeshWithIdentifier("bloke.tcf/forearm_right");
	auto forearm_right_model = graphics->newModel();
	forearm_right_model->material = forearm_right_material;
	forearm_right_model->mesh = forearm_right_mesh;
	forearm_right_actor_ = std::make_shared<tyga::Actor>();
	forearm_right_actor_->attachComponent(forearm_right_model);
	world->addActor(forearm_right_actor_);


	//blokes right hand
	auto hand_right_material = graphics->newMaterial();
	hand_right_material->colour = tyga::Vector3(0.f, 1.f, 0.f);
	auto hand_right_mesh = graphics->newMeshWithIdentifier("bloke.tcf/hand_right");
	auto hand_right_model = graphics->newModel();
	hand_right_model->material = hand_right_material;
	hand_right_model->mesh = hand_right_mesh;
	hand_right_actor_ = std::make_shared<tyga::Actor>();
	hand_right_actor_->attachComponent(hand_right_model);
	world->addActor(hand_right_actor_);


	//blokes right leg
	auto leg_right_material = graphics->newMaterial();
	leg_right_material->colour = tyga::Vector3(0.f, 1.f, 0.f);
	auto leg_right_mesh = graphics->newMeshWithIdentifier("bloke.tcf/leg_right");
	auto leg_right_model = graphics->newModel();
	leg_right_model->material = leg_right_material;
	leg_right_model->mesh = leg_right_mesh;
	leg_right_actor_ = std::make_shared<tyga::Actor>();
	leg_right_actor_->attachComponent(leg_right_model);
	world->addActor(leg_right_actor_);


	//blokes right shin
	auto shin_right_material = graphics->newMaterial();
	shin_right_material->colour = tyga::Vector3(0.f, 1.f, 0.f);
	auto shin_right_mesh = graphics->newMeshWithIdentifier("bloke.tcf/shin_right");
	auto shin_right_model = graphics->newModel();
	shin_right_model->material = shin_right_material;
	shin_right_model->mesh = shin_right_mesh;
	shin_right_actor_ = std::make_shared<tyga::Actor>();
	shin_right_actor_->attachComponent(shin_right_model);
	world->addActor(shin_right_actor_);



	//blokes right foot
	auto foot_right_material = graphics->newMaterial();
	foot_right_material->colour = tyga::Vector3(0.f, 1.f, 0.f);
	auto foot_right_mesh = graphics->newMeshWithIdentifier("bloke.tcf/foot_right");
	auto foot_right_model = graphics->newModel();
	foot_right_model->material = foot_right_material;
	foot_right_model->mesh = foot_right_mesh;
	foot_right_actor_ = std::make_shared<tyga::Actor>();
	foot_right_actor_->attachComponent(foot_right_model);
	world->addActor(foot_right_actor_);


	//blokes left leg
	auto leg_left_material = graphics->newMaterial();
	leg_left_material->colour = tyga::Vector3(0.f, 1.f, 0.f);
	auto leg_left_mesh = graphics->newMeshWithIdentifier("bloke.tcf/leg_left");
	auto leg_left_model = graphics->newModel();
	leg_left_model->material = leg_left_material;
	leg_left_model->mesh = leg_left_mesh;
	leg_left_actor_ = std::make_shared<tyga::Actor>();
	leg_left_actor_->attachComponent(leg_left_model);
	world->addActor(leg_left_actor_);


	//blokes left shin
	auto shin_left_material = graphics->newMaterial();
	shin_left_material->colour = tyga::Vector3(0.f, 1.f, 0.f);
	auto shin_left_mesh = graphics->newMeshWithIdentifier("bloke.tcf/shin_left");
	auto shin_left_model = graphics->newModel();
	shin_left_model->material = shin_left_material;
	shin_left_model->mesh = shin_left_mesh;
	shin_left_actor_ = std::make_shared<tyga::Actor>();
	shin_left_actor_->attachComponent(shin_left_model);
	world->addActor(shin_left_actor_);


	//blokes left foot
	auto foot_left_material = graphics->newMaterial();
	foot_left_material->colour = tyga::Vector3(0.f, 1.f, 0.f);
	auto foot_left_mesh = graphics->newMeshWithIdentifier("bloke.tcf/foot_left");
	auto foot_left_model = graphics->newModel();
	foot_left_model->material = foot_left_material;
	foot_left_model->mesh = foot_left_mesh;
	foot_left_actor_ = std::make_shared<tyga::Actor>();
	foot_left_actor_->attachComponent(foot_left_model);
	world->addActor(foot_left_actor_);

	//create the particles and put a system on each back wheel and set the wheel as the anchor and sink
	//had to use <class ToyParticles> as it for some reason disliked not having the class part
	auto toy_particlesRightWheel = std::make_shared<class ToyParticles>();
	toy_particlesRightWheel->addToWorld(world);
	toy_particlesRightWheel->setSource(wheel_actor_[3]);
	toy_particlesRightWheel->setSink(wheel_actor_[3]);

	auto toy_particlesLeftWheel = std::make_shared<class ToyParticles>();
	toy_particlesLeftWheel->addToWorld(world);
	toy_particlesLeftWheel->setSource(wheel_actor_[2]);
	toy_particlesLeftWheel->setSink(wheel_actor_[2]);

}

void Badger::
actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor)
{
    auto world = tyga::ActorWorld::defaultWorld();

    world->removeActor(physics_actor_);
}

void Badger::
actorClockTick(std::shared_ptr<tyga::Actor> actor)
{
    const float time = tyga::BasicWorldClock::CurrentTime();
    const float delta_time = tyga::BasicWorldClock::CurrentTickInterval();

    auto physics_local_xform = tyga::Matrix4x4(0.75f,     0,     0,     0,
                                                   0,   1.f,     0,     0,
                                                   0,     0,  1.5f,     0,
                                                   0,     1,     0,     1);
    auto physics_xform = physics_local_xform * actor->Transformation();
    physics_actor_->setTransformation(physics_xform);

    const float WHEEL_CIRCUMFERENCE = float(M_PI);
    const float WHEEL_BASE = 2.065f;
    const float MAX_SPEED = 10.f;
    const float MAX_WHEEL_TURN_ANGLE = 0.35f; // radians


	//animation start and stop times for the smoothsteps and lerps
	const float anim_start_time = 0.f;
	const float anim_stop_time = 3.f;
	const float anim_start_timeLT = 3.f;
	const float anim_stop_timeLT = 4.f;
	const float anim_start_timeRT = 4.f;
	const float anim_stop_timeRT = 7.f;
	const float anim_start_timeE = 7.f;
	const float anim_stop_timeE = 9.f;


	

	//below are all the transformations applied to each componnet
	//they are all their local transforms and each child such as the wheels are multiplied by the parent xfrom e.g for the badger the parent xform is the chassis xform
	auto chassis_xform = JoshAinley::translate(0, 0.756, -0.075);
	auto handlebar_xform = JoshAinley::rotateX(-0.6769084971) * JoshAinley::rotateY(turnAngle_) * JoshAinley::translate(0, 0.633, 0.411) *  chassis_xform;
	auto luggage_rack_xform = JoshAinley::translate(0, 0.630, -1.075) * chassis_xform;
	auto LFwheel_xform =  JoshAinley::rotateX(-turnAngle_) * JoshAinley::rotateZ(-1.5708) * JoshAinley::translate(0.654, -0.235, 1.065) *  chassis_xform;
	auto LBwheel_xform =  JoshAinley::rotateZ(-1.5708) * JoshAinley::translate(0.654, -0.235, -1) *  chassis_xform;
	auto RFwheel_xform =  JoshAinley::rotateX(turnAngle_) * JoshAinley::rotateZ(1.5708) * JoshAinley::translate(-0.654f, -0.235, 1.065) *  chassis_xform;
	auto RBwheel_xform =  JoshAinley::rotateZ(1.5708) * JoshAinley::translate(-0.654, -0.235, -1) *  chassis_xform;

	
	//the bloke each component is again multiplied by their parent such as the hand is multiplied by th eforearm xform and so on.
	//hardcoded the hierarchy by multiplied the parent xform after the childs local xform
	auto posPelvis = JoshAinley::translate(0, 0.757, -0.24) * chassis_xform;
	auto posTorso = (JoshAinley::rotateX(42 * M_PI /180 ) * JoshAinley::rotateY(-5 * M_PI/180) * JoshAinley::rotateZ(6 * M_PI/180) * posPelvis);
	auto posHelmet = (JoshAinley::rotateX(-21* M_PI / 180) * JoshAinley::rotateY(2 * M_PI / 180) * JoshAinley::rotateZ(-8 * M_PI /180) * JoshAinley::translate(0, 0.544, -0.019) * posTorso);

	//the arm is the root node for the fore arm and hand
	auto posArmLeft = (JoshAinley::rotateX(-45* M_PI / 180) * JoshAinley::rotateY(22* M_PI / 180) * JoshAinley::rotateZ(-8* M_PI / 180)) * JoshAinley::translate(0.213, 0.39, -0.052)* posTorso;
	auto posForeArmLeft = (JoshAinley::rotateX(-66* M_PI / 180) * JoshAinley::translate(0.04, -0.332, 0.024)* posArmLeft);
	auto posHandLeft = JoshAinley::translate(-0.003, -0.265, 0.048)* posForeArmLeft;

	auto posArmRight = (JoshAinley::rotateX(-27 * M_PI / 180) * JoshAinley::rotateY(-11* M_PI / 180) * JoshAinley::rotateZ(6 * M_PI / 180)) * JoshAinley::translate(-0.213, 0.39, -0.052) * posTorso;
	auto posForeArmRight = (JoshAinley::rotateX(-79* M_PI / 180) * JoshAinley::translate(-0.04, -0.332, 0.024) * posArmRight);
	auto posHandRight = JoshAinley::translate(0.003, -0.265, 0.048)* posForeArmRight;

	//leg is the root node for the shin and foot
	auto posLegRight = (JoshAinley::rotateX(-16* M_PI / 180) * JoshAinley::rotateY(-18* M_PI / 180) * JoshAinley::rotateZ(-9* M_PI / 180)) * JoshAinley::translate(-0.101, -0.074, 0.008)* posPelvis;
	auto posShinRight = (JoshAinley::rotateX(30 * M_PI / 180) * JoshAinley::translate(-0.041, -0.462, -0.039)* posLegRight);
	auto posFootRight =   JoshAinley::translate(-0.019, -0.416, 0.006)* posShinRight;

	auto posLegLeft = (JoshAinley::rotateX(-16* M_PI / 180) * JoshAinley::rotateY(18* M_PI / 180) * JoshAinley::rotateZ(9* M_PI / 180)) * JoshAinley::translate(0.101, -0.074, 0.008)* posPelvis;
	auto posShinLeft =  (JoshAinley::rotateX(30* M_PI / 180) *JoshAinley::translate(0.041, -0.462, -0.039)* posLegLeft);
	auto posFootLeft =  JoshAinley::translate(0.019, -0.416, 0.006)* posShinLeft;


	//equations to calculation wheelspin and heading angle
	float DistanceTravelled = speed_ * delta_time;
	DeltaWheelSpin += (float(2 * M_PI)) * (DistanceTravelled / WHEEL_CIRCUMFERENCE);
	DeltaHeadingAngle = (DistanceTravelled * sin(turnAngle_)) / WHEEL_CIRCUMFERENCE;

	//this is the loop 
	//the looptime is what keeps the badger restarting
	//so after the first full animation loop time should equal about 12 or the time at the end of the animation
	if (time < 3.f + loopTime)
	{
		//animation for going straight 
		float s = JoshAinley::SmoothStep(anim_start_time + loopTime, 5.f + loopTime, time );
		speed_ = JoshAinley::LerpFloat(0, MAX_SPEED, s);
	}
	else if (time < 4.f + loopTime)
	{
		//after 4 secs the animation goes into the first turn and this is the smoothstep turn to get the turnangle
		float s = JoshAinley::SmoothStep(anim_start_timeLT + loopTime, anim_stop_timeLT + loopTime, time);
		  turnAngle_ = JoshAinley::LerpFloat(0.f, MAX_WHEEL_TURN_ANGLE, s);
	}

	else if ( time < 7.f + loopTime)
	{
		//after 7 secs the animation goes into the second turn and goes from the last turn angle to 0 and then turns after the opposite max turn angle
		 float s = JoshAinley::SmoothStep(anim_start_timeRT + loopTime, 5.f + loopTime, time);
		 turnAngle_ = JoshAinley::LerpFloat(MAX_WHEEL_TURN_ANGLE, -MAX_WHEEL_TURN_ANGLE, s);
	}
	else if ( time < 9.f + loopTime)
	{
		//after 9secs in total the turn angle is set back to 0
		float s = JoshAinley::SmoothStep(anim_start_timeE + loopTime, anim_stop_timeE + loopTime, time);
		turnAngle_ = JoshAinley::LerpFloat(-MAX_WHEEL_TURN_ANGLE, 0.f, s);
	}
	else if (time < 12.f + loopTime)
	{
		//after 12 secs the car comes to a smooth stop
		//animation for going straight 
		float s = JoshAinley::SmoothStep(0.f + loopTime, 4.f + loopTime, time);
		speed_ = JoshAinley::LerpFloat(speed_, 0, s);
	}
	else
	{
		loopTime = time;
	}
	

	//rotation matrix to get the wheels to spin
	//reason fo rtwo is because one needs to be reversed to make the right wheels go forward instead of backwards
	tyga::Matrix4x4 WheelspinRotateL = JoshAinley::rotateY(DeltaWheelSpin);
	tyga::Matrix4x4 WheelspinRotateR = JoshAinley::rotateY(-DeltaWheelSpin);

	//derived the direction from the matrix of the chassis and delta position is updated with direction
	tyga::Vector3 direction = { chassis_xform._20, chassis_xform._21, chassis_xform._22 };
	tyga::Vector3 deltaPostion = DistanceTravelled * direction;

	//the rotate YZZZ is the rotae the wheels in the direction the badger is heading
	tyga::Matrix4x4 RotateYZZZ = JoshAinley::rotateY(DeltaHeadingAngle);
	//the xformfwd moves the badger to place it should be in the animation
	tyga::Matrix4x4 xformFwd = JoshAinley::translate(deltaPostion.x, deltaPostion.y, deltaPostion.z);
	
	//sets the root xform
	auto root = actor->Transformation();

	//makes the whole animation using these three xforms and multiplying by the root xform is so the camera can follow
	//this XFORM does the animation update this one and all will change accordingly
	auto ActorTransform = RotateYZZZ * xformFwd * root;

	chassis_actor_->setTransformation( chassis_xform * ActorTransform );
	handlebar_actor_->setTransformation( handlebar_xform * ActorTransform );
	luggage_rack_actor_->setTransformation(luggage_rack_xform * ActorTransform );
	wheel_actor_[0]->setTransformation(WheelspinRotateL * LFwheel_xform *   ActorTransform );
	wheel_actor_[2]->setTransformation(WheelspinRotateL * LBwheel_xform  * ActorTransform);
	wheel_actor_[1]->setTransformation(WheelspinRotateR * RFwheel_xform *  ActorTransform );
	wheel_actor_[3]->setTransformation(WheelspinRotateR * RBwheel_xform * ActorTransform );
	//camera follows badger actor
	actor->setTransformation(ActorTransform);

	//this whole part is just making the bloke follow the badger animation in the same pose 
	helmet_actor_->setTransformation(posHelmet * ActorTransform);
	torso_actor_->setTransformation(posTorso * ActorTransform);
	pelvis_actor_->setTransformation(posPelvis * ActorTransform);

	arm_left_actor_->setTransformation(posArmLeft * ActorTransform);
	forearm_left_actor_->setTransformation(posForeArmLeft * ActorTransform);
	hand_left_actor_->setTransformation(posHandLeft * ActorTransform);

	arm_right_actor_->setTransformation(posArmRight * ActorTransform);
	forearm_right_actor_->setTransformation(posForeArmRight * ActorTransform);
	hand_right_actor_->setTransformation(posHandRight * ActorTransform);

	leg_left_actor_->setTransformation(posLegLeft * ActorTransform);
	shin_left_actor_->setTransformation(posShinLeft * ActorTransform);
	foot_left_actor_->setTransformation(posFootLeft * ActorTransform);

	leg_right_actor_->setTransformation(posLegRight * ActorTransform);
	shin_right_actor_->setTransformation(posShinRight * ActorTransform);
	foot_right_actor_->setTransformation(posFootRight * ActorTransform);

	

}
