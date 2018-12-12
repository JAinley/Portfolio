#include "MyDemo.hpp"
#include "Badger.hpp"
#include "Camera.hpp"
#include "ToyDrone.hpp"
#include "MyPhysicsCentre.hpp"

#include <tyga/Application.hpp>
#include <tyga/ActorWorld.hpp>
#include <tyga/InputStateProtocol.hpp>
#include <tyga/BasicRenderer.hpp>
#include <tyga/GraphicsCentre.hpp>
#include <tyga/BasicWorldClock.hpp>
#include <tyga/Math.hpp>

#include <iostream>


const tyga::Vector3 MyDemo::MIN_BOUND = tyga::Vector3(-20, 0.3f, -10);
const tyga::Vector3 MyDemo::MAX_BOUND = tyga::Vector3(20, 1.5f, 10);

void MyDemo::
applicationWindowWillInit(int& width,
                          int& height,
                          int& sample_count,
                          bool& windowed)
{
    width = 1024;
    height = 576;

    std::cout << "Animation and Simulation Programming" << std::endl;
    std::cout << "Badger Demo" << std::endl << std::endl;
    std::cout << "  Use the gamepad thumbsticks to control the ToyBadger vehicle." << std::endl;
    std::cout << "  Hold the right shoulder button to control the camera." << std::endl;
    std::cout << "  Press F2 to swap camera modes." << std::endl;
    std::cout << "  Press F5 to reset the ToyDrones." << std::endl;
    std::cout << "  Press enter to add more ToyDrones." << std::endl;
    std::cout << "  Hold spacebar to push the ToyDrones." << std::endl << std::endl;
}

void MyDemo::
applicationDidStart()
{
    renderer_ = std::make_shared<tyga::BasicRenderer>();
    tyga::Application::setWindowViewDelegate(renderer_);

    tyga::Application::addRunloopTask(MyPhysicsCentre::defaultCentre());
    tyga::Application::addRunloopTask(tyga::GraphicsCentre::defaultCentre());
    tyga::Application::addRunloopTask(tyga::ActorWorld::defaultWorld());

    tyga::Application::setRunloopFrequency(60);


    auto world = tyga::ActorWorld::defaultWorld();
    auto graphics = tyga::GraphicsCentre::defaultCentre();
    auto physics = MyPhysicsCentre::defaultCentre();


    auto floor_model = graphics->newModel();
    floor_model->material = graphics->newMaterial();
    floor_model->material->colour = tyga::Vector3(0.9f, 0.9f, 0.25f);
    floor_model->mesh = graphics->newMeshWithIdentifier("cube");
    auto floor_actor = std::make_shared<tyga::Actor>();
    floor_actor->attachComponent(floor_model);
    auto floor_xform = tyga::Matrix4x4(      80,       0,       0,       0,
                                              0,    0.2f,       0,       0,
                                              0,       0,      80,       0,
                                              0,   -0.1f,       0,       1);
    floor_actor->setTransformation(floor_xform);
    world->addActor(floor_actor);

    auto block_material = graphics->newMaterial();
    block_material->colour = tyga::Vector3(1, 0.33f, 0);
    auto block_mesh = graphics->newMeshWithIdentifier("cube");
    for (int i = 0; i<4; ++i) {
        auto block_model = graphics->newModel();
        block_model->material = block_material;
        block_model->mesh = block_mesh;
        auto block_actor = std::make_shared<tyga::Actor>();
        block_actor->attachComponent(block_model);
        float x = -12.f + 8 * i;
        auto block_xform = tyga::Matrix4x4(      1,       0,       0,       0,
                                                 0,       1,       0,       0,
                                                 0,       0,       1,       0,
                                                 x,    0.5f,       0,       1);
        block_actor->setTransformation(block_xform);
        world->addActor(block_actor);
    }


    camera_ = std::make_shared<Camera>();
    camera_->addToWorld(world);
    camera_->setHeadingAngle(0.2f);
    camera_->setPanDistance(30);


    toy_badger_ = tyrone::ToyBadger::makeBadgerWithBloke(world);
    auto toy_badger_xform = tyga::Matrix4x4( 1, 0, 0, 0,
                                             0, 1, 0, 0,
                                             0, 0, 1, 0,
                                            10, 0, 0, 1);
    toy_badger_->Actor()->setTransformation(toy_badger_xform);
    auto toy_badger_box = physics->newBox();
    toy_badger_->boundsActor()->attachComponent(toy_badger_box);


    badger_ = std::make_shared<Badger>();
    badger_->addToWorld(world);
    auto badger_box = physics->newBox();
    badger_->boundsActor()->attachComponent(badger_box);


    addToys();
}

void MyDemo::
applicationRunloopWillBegin()
{
    tyga::BasicWorldClock::update();

    const float time = tyga::BasicWorldClock::CurrentTime();
    if (trigger_time_ < time) {
        for (auto toy : toys_) {
            toy->trigger();
        }
        trigger_time_ = std::numeric_limits<float>::max();
    }

    auto camera_xform = tyga::Matrix4x4(       1,       0,       0,       0,
                                               0,       1,       0,       0,
                                               0,       0,       1,       0,
                                               0,       1,       0,       1);
    switch (camera_mode_)
    {
    case MyDemo::kCameraStatic:
        camera_->Actor()->setTransformation(camera_xform);
        break;
    case MyDemo::kCameraTracking:
        camera_->Actor()->setTransformation(
            camera_xform * badger_->Actor()->Transformation());
        break;
    }
}

void MyDemo::
applicationRunloopDidEnd()
{
    renderer_->setGraphicsScene(tyga::GraphicsCentre::defaultCentre()->scene());
}

void MyDemo::
applicationWillStop()
{
}

void MyDemo::
applicationInputStateChanged(
    std::shared_ptr<tyga::InputStateProtocol> input_state)
{
    if (input_state->gamepadPresent(0))
    {
        if (input_state->gamepadButtonDownCount(
            0, tyga::kInputGamepadButtonRightShoulder) > 0)
        {
            float camera_heading_speed = input_state
                ->gamepadAxisPosition(0, tyga::kInputGamepadAxisRightThumbX);
            camera_->setHeadingSpeed(camera_heading_speed);
            float camera_pan_speed = -input_state
                ->gamepadAxisPosition(0, tyga::kInputGamepadAxisLeftThumbY);
            camera_->setPanSpeed(camera_pan_speed);
        }
        else
        {
            float toy_badger_speed = input_state
                ->gamepadAxisPosition(0, tyga::kInputGamepadAxisLeftThumbY);
            toy_badger_->setSpeed(toy_badger_speed);
            float toy_badger_turn = input_state
                ->gamepadAxisPosition(0, tyga::kInputGamepadAxisRightThumbX);
            toy_badger_->setTurnAngle(toy_badger_turn);
        }
    }
    else
    {
        float toy_badger_speed = input_state
            ->keyboardAxisPosition(tyga::kInputKeyboardAxisUpDown);
        toy_badger_->setSpeed(toy_badger_speed);
        float toy_badger_turn = input_state
            ->keyboardAxisPosition(tyga::kInputKeyboardAxisLeftRight);
        toy_badger_->setTurnAngle(toy_badger_turn);
    }

    if (input_state->keyboardKeyDownCount(tyga::kInputKeyF2) == 1) {
        camera_mode_ = CameraMode((camera_mode_ + 1) % kCameraMAX);
        switch (camera_mode_)
        {
        case MyDemo::kCameraStatic:
            camera_->setHeadingAngle(0.2f);
            camera_->setPanDistance(30);
            break;
        case MyDemo::kCameraTracking:
            camera_->setHeadingAngle(2);
            camera_->setPanDistance(5);
            break;
        }
    }

    if (input_state->keyboardKeyDownCount(tyga::kInputKeyF5) == 1) {
        resetToys();
    }

    if (input_state->keyboardKeyDownCount(tyga::kInputKeyEnter) == 1) {
        addToys();
    }

    if (input_state->keyboardKeyDownCount(tyga::kInputKeySpace) > 0) {
        pushToys();
    }
}

void MyDemo::
resetToys()
{
    for (auto& toy : toys_) {
        toy->removeFromWorld();
    }

    toys_.clear();

    addToys();
}

void MyDemo::
addToys()
{
    std::uniform_int_distribution<int> n_rand(10, 50);
    std::uniform_real_distribution<float> x_rand(MIN_BOUND.x, MAX_BOUND.x);
    std::uniform_real_distribution<float> y_rand(MIN_BOUND.y, MAX_BOUND.y);
    std::uniform_real_distribution<float> z_rand(MIN_BOUND.z, MAX_BOUND.z);
    std::uniform_real_distribution<float> m_rand(0.75f, 1.25f);

    auto world = tyga::ActorWorld::defaultWorld();

    size_t current_num_toys = toys_.size();
    toys_.resize(current_num_toys + n_rand(rand));
    for (size_t i = current_num_toys; i < toys_.size(); ++i) {
        auto& toy = toys_[i];
        toy = std::make_shared<ToyDrone>();
        toy->addToWorld(world);
        auto position = tyga::Vector3(x_rand(rand), y_rand(rand), z_rand(rand));
        auto mass = m_rand(rand);
        toy->reset(position, mass);
    }
}

void MyDemo::
triggerToys()
{
    std::uniform_real_distribution<float> x_rand(-0.2f, 0.2f);
    std::uniform_real_distribution<float> z_rand(-0.2f, 0.2f);

    for (auto toy : toys_) {
        auto dir = tyga::unit(tyga::Vector3(x_rand(rand), 1, z_rand(rand)));
        auto force = 600 * dir;
        toy->applyForce(force);
    }

    std::uniform_real_distribution<float> t_rand(1, 3);
    trigger_time_ = tyga::BasicWorldClock::CurrentTime() + t_rand(rand);
}

void MyDemo::
pushToys()
{
    const float time = tyga::BasicWorldClock::CurrentTime();
    const float SECS_PER_TURN = 1.5f;
    const float theta = 2.f * (float)M_PI * std::fmodf(time, SECS_PER_TURN) / SECS_PER_TURN;
    std::uniform_real_distribution<float> y_rand((float)M_PI * 0.2f, (float)M_PI * 0.3f);

    const auto& target_xform = toy_badger_->Actor()->Transformation();
    const tyga::Vector3 target_pos(target_xform._30, target_xform._31, target_xform._32);

    for (auto toy : toys_) {
        const auto& xform = toy->Actor()->Transformation();
        const tyga::Vector3 pos(xform._30, xform._31, xform._32);
        const tyga::Vector3 to_target = target_pos - pos;
        const float phi = y_rand(rand);
        const auto dir = tyga::Vector3(sinf(phi) * cosf(theta), cosf(phi), sinf(phi) * -sinf(theta));
        const auto force = 15.f * dir + 0.1f * to_target;
        toy->applyForce(force);
    }
}
