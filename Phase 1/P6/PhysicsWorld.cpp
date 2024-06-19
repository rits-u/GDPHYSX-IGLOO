#include "PhysicsWorld.h"
using namespace P6;

void PhysicsWorld::AddParticle(P6Particle* toAdd) {
	Particles.push_back(toAdd);	
	forceRegistry.Add(toAdd, &Gravity); //HELP
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

		if (num >= 6) {
			num = 1;

		}
		else {
			num++;
		}
		std::cout << num << " particle: " << (*p)->getPosition() << std::endl;
	}
}

void PhysicsWorld::CheckIfDone() {
	for (std::list<P6Particle*>::iterator p = Particles.begin();

		p != Particles.end();

		p++
		)
	{
		(*p)->IsAtOrigin();
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