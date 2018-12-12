#pragma once

#include <tyga/ActorDelegate.hpp>
#include <tyga/GraphicsCentre.hpp>

class MyParticleSystem : public tyga::GraphicsSpriteDelegate,
                         public std::enable_shared_from_this<MyParticleSystem>
{
public:

    struct Particle {
        // TODO: what per-particle data do you need?
        tyga::Vector3 position;
        tyga::Vector3 velocity;
		bool setAlive = false;
		float duration=2.f;
    };

    // TODO: what per-system data do you need?
    std::vector<Particle> particles;

    std::string
    graphicsSpriteTexture() const override;

    int
    graphicsSpriteVertexCount() const override;

    void
    graphicsSpriteGenerate(
        tyga::GraphicsSpriteVertex vertex_array[]) const override;
};

class ToyParticles : public tyga::ActorDelegate
                     
{
public:

    void
    setSource(std::shared_ptr<tyga::Actor>);

    void
    setSink(std::shared_ptr<tyga::Actor>);

private:
	

	float counter{ 0 };
	float duration = 3.f;


    virtual void
    actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorClockTick(std::shared_ptr<tyga::Actor> actor) override;

    std::shared_ptr<tyga::GraphicsSprite> graphic_sprite_;
    std::shared_ptr<tyga::Actor> source_actor_;
    std::shared_ptr<tyga::Actor> sink_actor_;

    std::shared_ptr<MyParticleSystem> particle_system_;
};
