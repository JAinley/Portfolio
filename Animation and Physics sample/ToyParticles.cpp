#include "ToyParticles.hpp"
#include "MyUtils.hpp"

#include <tyga/Actor.hpp>
#include <tyga/BasicWorldClock.hpp>
#include <tyga/Math.hpp>
#include <tyga/ActorWorld.hpp>
#include <tyga/GraphicsCentre.hpp>

void ToyParticles::
setSource(std::shared_ptr<tyga::Actor> source)
{
    source_actor_ = source;
}

void ToyParticles::
setSink(std::shared_ptr<tyga::Actor> sink)
{
    sink_actor_ = sink;
}

void ToyParticles::
actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor)
{
    auto world = tyga::ActorWorld::defaultWorld();
    auto graphics = tyga::GraphicsCentre::defaultCentre();

    particle_system_ = std::make_shared<MyParticleSystem>();
    graphic_sprite_ = graphics->newSpriteWithDelegate(particle_system_);
}

void ToyParticles::
actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor)
{
}

void ToyParticles::
actorClockTick(std::shared_ptr<tyga::Actor> actor)
{
    const float current_time = tyga::BasicWorldClock::CurrentTime();
    const float delta_time = tyga::BasicWorldClock::CurrentTickInterval();

    // TODO: remove this test code immediately
	particle_system_->particles.resize(50);

    // TODO: obtain position and direction from emitter

	//sets the postions and direction whihc is derived from the source matrix
    tyga::Matrix4x4 source_xform = source_actor_->Transformation();
	tyga::Vector3 source_position = { source_xform._30, source_xform._31, source_xform._32 };
	tyga::Vector3 source_direction = {source_xform._20, source_xform._21, source_xform._22};
	tyga::Vector3 InitialVel{ 0,0,0 };
	tyga::Vector3 newPos;

	//loops through each particle each tick like a for loop and checks to see if a particle is dead
	if (counter < 50)
	{
	if (particle_system_->particles[counter].setAlive == false)
	{
		//if the particle is deaqd its updated with the source postion and given the starting velocity 
		tyga::Vector3 newPos = JoshAinley::Euler(source_position, InitialVel, delta_time);
		//particle_system_->particles[counter].setAlive = true;
		particle_system_->particles[counter].position = newPos;
		particle_system_->particles[counter].velocity = InitialVel;

	}
		//if particle is true then the lifetime (duration) will decrease
		else if (particle_system_->particles[counter].setAlive == true)
		{
		
		particle_system_->particles[counter].duration - 1.f;

		/*if the duration decreases to 0 then the particles duration gets reset and the particle is set to false to start the loop again
		  so it can be set the position of the source again and can be reused

		  I used a short lifespan for the particles so they wouldnt trail for too long on the badger and would give a more real effect
		  TODO later would be to  add alpha on the texture so it fades out near death and then use stochastic random!
		*/
		for (int index = 0; index < particle_system_->particles.size(); index++)
		{
			if (particle_system_->particles[index].duration <= 0) {
				//newPos = source_position;
				particle_system_->particles[index].setAlive = false;
				particle_system_->particles[index].duration = 2.0f;
			}

		}
		}
		

	//increments the counter to next particle
		counter++;
	}

	//if end of particles reached then counter gets reset to 0 to loop through the particles again
	if (counter == 50) {
		counter = 0;
	}

    // TODO: birth and/or kill any particles for this frame

    // TODO: obtain position from attractor
    tyga::Matrix4x4& sink_xform = sink_actor_->Transformation();
    tyga::Vector3 sink_position;

    // TODO: loop and update position and velocity of living particles


	
}


std::string MyParticleSystem::
graphicsSpriteTexture() const
{
    return "fire.png";
}

int MyParticleSystem::
graphicsSpriteVertexCount() const
{
    // NB: you may need to adjust this count if you keep dead particles
    return (int)particles.size();
}

void MyParticleSystem::
graphicsSpriteGenerate(tyga::GraphicsSpriteVertex vertex_array[]) const
{
    // NB: you may need to adjust this if you want to control the sprite look
    for (unsigned int i=0; i<particles.size(); ++i) {
        vertex_array[i].position = particles[i].position;
        vertex_array[i].size = 0.5f;
        vertex_array[i].colour = tyga::Vector3(1, 1, 1);
        vertex_array[i].alpha = 1.f;
        vertex_array[i].rotation = 0.f; // NB: has no effect in basic renderer
    }
}
