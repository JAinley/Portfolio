#include "MyDemo.hpp"
#include "WillingCube.hpp"
#include "HopefulCone.hpp"
#include "IndignantCylinder.hpp"
#include "SteadySphere.hpp"

#include <tyga/Application.hpp>
#include <tyga/ActorWorld.hpp>
#include <tyga/InputStateProtocol.hpp>
#include <tyga/BasicRenderer.hpp>
#include <tyga/GraphicsCentre.hpp>
#include <tyga/BasicWorldClock.hpp>
#include <tyga/Math.hpp>

void MyDemo::
applicationWindowWillInit(int& width,
                          int& height,
                          int& sample_count,
                          bool& windowed)
{
    width = 1024;
    height = 576;
}

void MyDemo::
applicationDidStart()
{
    renderer_ = std::make_shared<tyga::BasicRenderer>();
    tyga::Application::setWindowViewDelegate(renderer_);

    tyga::Application::addRunloopTask(tyga::GraphicsCentre::defaultCentre());
    tyga::Application::addRunloopTask(tyga::ActorWorld::defaultWorld());

    tyga::Application::setRunloopFrequency(60);


    auto world = tyga::ActorWorld::defaultWorld();
    auto graphics = tyga::GraphicsCentre::defaultCentre();


    auto camera = graphics->newCamera();
    camera->vertical_field_of_view_radians = 0.8f;

    auto camera_actor = std::make_shared<tyga::Actor>();
    camera_actor->attachComponent(camera);
    auto camera_xform = tyga::Matrix4x4(       1,       0,       0,       0,
                                               0,       0,       1,       0,
                                               0,      -1,       0,       0,
                                               0,     -13,       3,       1);
    camera_actor->setTransformation(camera_xform);

    world->addActor(camera_actor);


    auto floor_model = graphics->newModel();
    floor_model->material = graphics->newMaterial();
    floor_model->mesh = graphics->newMeshWithIdentifier("cube");

    auto floor_actor = std::make_shared<tyga::Actor>();
    floor_actor->attachComponent(floor_model);
    auto floor_xform = tyga::Matrix4x4(      10,       0,       0,       0,
                                              0,      10,       0,       0,
                                              0,       0,    0.2f,       0,
                                              0,       0,   -0.1f,       1);
    floor_actor->setTransformation(floor_xform);

    world->addActor(floor_actor);


    auto willing_cube = std::make_shared<WillingCube>();
    willing_cube->addToWorld(world);

    auto hopeful_cone = std::make_shared<HopefulCone>();
    hopeful_cone->addToWorld(world);

    auto steady_sphere = std::make_shared<SteadySphere>();
    steady_sphere->addToWorld(world);

	auto Indignant_Cylinder = std::make_shared<IndignantCylinder>();
	Indignant_Cylinder->addToWorld(world);
}

void MyDemo::
applicationRunloopWillBegin()
{
    tyga::BasicWorldClock::update();
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
}
