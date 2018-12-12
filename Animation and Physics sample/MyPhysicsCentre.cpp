#include "MyPhysicsCentre.hpp"
#include "MyUtils.hpp"
#include <tyga/BasicWorldClock.hpp>
#include <tyga/Log.hpp>


tyga::Vector3 PhysicsObject::
position() const
{
    auto actor = this->Actor();
    if (actor != nullptr) {
        const auto& xform = actor->Transformation();
        return tyga::Vector3(xform._30, xform._31, xform._32);
    }
    return tyga::Vector3();
}

tyga::Vector3 PhysicsPlane::
normal() const
{
    auto actor = this->Actor();
    if (actor != nullptr) {
        const auto& xform = actor->Transformation();
        return tyga::Vector3(xform._20, xform._21, xform._22);
    }
    return tyga::Vector3();
}

tyga::Vector3 PhysicsBox::
U() const
{
    auto actor = this->Actor();
    if (actor != nullptr) {
        const auto& xform = actor->Transformation();
        return tyga::Vector3(xform._00, xform._01, xform._02);
    }
    return tyga::Vector3();
}

tyga::Vector3 PhysicsBox::
V() const
{
    auto actor = this->Actor();
    if (actor != nullptr) {
        const auto& xform = actor->Transformation();
        return tyga::Vector3(xform._10, xform._11, xform._12);
    }
    return tyga::Vector3();
}

tyga::Vector3 PhysicsBox::
W() const
{
    auto actor = this->Actor();
    if (actor != nullptr) {
        const auto& xform = actor->Transformation();
        return tyga::Vector3(xform._20, xform._21, xform._22);
    }
    return tyga::Vector3();
}

std::shared_ptr<MyPhysicsCentre> MyPhysicsCentre::default_centre_;

std::shared_ptr<MyPhysicsCentre> MyPhysicsCentre::
defaultCentre()
{
    if (default_centre_ == nullptr) {
        default_centre_ = std::make_shared<MyPhysicsCentre>();
    }
    return default_centre_;
}

template<typename T> static void
_prune(std::list<T>& list)
{
    for (auto it = list.begin(); it != list.end(); ) {
        if (it->expired()) {
            it = list.erase(it);
        } else {
            it++;
        }
    }
}

void MyPhysicsCentre::
pruneDeadObjects()
{
    _prune(planes_);
    _prune(spheres_);
    _prune(boxes_);
}

std::shared_ptr<PhysicsPlane> MyPhysicsCentre::
newPlane()
{
    auto new_plane = std::make_shared<PhysicsPlane>();
    planes_.push_back(new_plane);
    return new_plane;
}

std::shared_ptr<PhysicsSphere> MyPhysicsCentre::
newSphere()
{
    auto new_sphere = std::make_shared<PhysicsSphere>();
    spheres_.push_back(new_sphere);
    return new_sphere;
}

std::shared_ptr<PhysicsBox> MyPhysicsCentre::
newBox()
{
    auto new_box = std::make_shared<PhysicsBox>();
    boxes_.push_back(new_box);
    return new_box;
}

void MyPhysicsCentre::
runloopWillBegin()
{
    for (auto s_iter = spheres_.begin(); s_iter != spheres_.end(); s_iter++)
    {
        // only continue if a strong reference is available
        if (s_iter->expired()) continue;
        auto sphere = s_iter->lock();

        // very crude ground plane collision detection and response
        // TODO: this could be improved
        const auto& p = sphere->position();
        if (p.y < sphere->radius) {
            sphere->velocity.y = 0;
            auto actor = sphere->Actor();
            if (actor != nullptr) {
                auto xform = actor->Transformation();
                xform._31 = sphere->radius;
                actor->setTransformation(xform);
            }
        }
    }
}

void MyPhysicsCentre::
runloopExecuteTask()
{
    const float time = tyga::BasicWorldClock::CurrentTime();
    const float delta_time = tyga::BasicWorldClock::CurrentTickInterval();

    for (auto ptr : spheres_) {
        // only continue if a strong reference is available
        if (ptr.expired()) continue;
        auto model = ptr.lock();

        // only continue if the model is attached to an actor
        auto actor = model->Actor();
        if (actor == nullptr) continue;

        // TODO: perform the physics (dynamics) update
		tyga::Vector3 Gravity{ 0, (float)-9.81, 0 };
		tyga::Vector3 Postion = model->position();

		tyga::Vector3 drag = (0.7f * model->velocity);

		// acceleration = force + gravity / mass
		// model has the force already applied, gravity is already defined above, and the model knows its own mass
		tyga::Vector3 acceleration = (model->force + Gravity) - drag / model->mass;

		//this euler works out the models new velocity after the force is applied so when the force is 0 the velocity is mainained and the balls will drop in the direction of the velocity
		tyga::Vector3 vel = JoshAinley::Euler( model->velocity, acceleration, delta_time);
		
		//sets the models velocity as the new one
		model->velocity = vel;

		//bad name for the calculation!! calculates the new posiotn for the model using time and velocity and plus the models current position
		tyga::Vector3 euler = JoshAinley::Euler(Postion, model->velocity, delta_time);
		

		//sets the transformation using the eulers new positions
		auto pos = JoshAinley::translate(euler.x, euler.y, euler.z);
		
		actor->setTransformation(pos);
        // TODO: update the actor's transformation

        // reset the force
        model->force = tyga::Vector3(0,0,0);
    }
}

void MyPhysicsCentre::
runloopDidEnd()
{
    pruneDeadObjects();
}
