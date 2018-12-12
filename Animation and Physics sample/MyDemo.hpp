#pragma once

#include <tyrone/ToyBadger.hpp>
#include <tyga/Math.hpp>
#include <tyga/ApplicationDelegate.hpp>
#include <tyga/GraphicsRendererProtocol.hpp>

#include <random>
#include <vector>

class Badger;
class Camera;
class ToyDrone;

class MyDemo : public tyga::ApplicationDelegate
{

private:

    virtual void
    applicationWindowWillInit(int& width,
                              int& height,
                              int& sample_count,
                              bool& windowed);

    virtual void
    applicationDidStart() override;

    virtual void
    applicationRunloopWillBegin() override;

    virtual void
    applicationRunloopDidEnd() override;

    virtual void
    applicationWillStop() override;

    virtual void
    applicationInputStateChanged(
        std::shared_ptr<tyga::InputStateProtocol> input_state) override;

    void
    resetToys();

    void
    addToys();

    void
    triggerToys();

    void
    pushToys();

    std::shared_ptr<tyga::GraphicsRendererProtocol> renderer_;

    enum CameraMode { kCameraStatic, kCameraTracking, kCameraMAX };
    CameraMode camera_mode_{ kCameraTracking };

    std::shared_ptr<Camera> camera_;
    std::shared_ptr<tyrone::ToyBadger> toy_badger_;
    std::shared_ptr<Badger> badger_;

    std::minstd_rand rand;
    static const tyga::Vector3 MIN_BOUND;
    static const tyga::Vector3 MAX_BOUND;

    std::vector<std::shared_ptr<ToyDrone>> toys_;

    float trigger_time_{ std::numeric_limits<float>::max() };
};
