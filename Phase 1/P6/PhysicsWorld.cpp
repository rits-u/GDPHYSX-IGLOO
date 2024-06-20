#include "PhysicsWorld.h"
using namespace P6;

void PhysicsWorld::AddParticle(P6Particle* toAdd) {
	Particles.push_back(toAdd);	
	forceRegistry.Add(toAdd, &Gravity); 
}

void PhysicsWorld::Update(float time) {
	UpdateParticleList();
	forceRegistry.UpdateForces(time);

	int num = 0;

	for (std::list<P6Particle*>::iterator p = Particles.begin();
		p != Particles.end();
		p++
		)
	{
		(*p)->Update(time);
	}
}

void PhysicsWorld::CheckLifespan(float time) {
	for (std::list<P6Particle*>::iterator p = Particles.begin();
		p != Particles.end();
		p++)
	{
		if ((*p)->lifespan <= (int)time - (int)(*p)->spawnTime)
			(*p)->Destroy();
	}
}

void PhysicsWorld::UpdateParticleList() {
	Particles.remove_if(
		[](P6Particle* p) {
			return p->IsDestroyed();
		}
		//lambda expression
	);
}