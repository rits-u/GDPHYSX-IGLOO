#pragma once
#include <list>
#include "P6Particle.h"
#include "ForceRegistry.h"
#include "GravityForceGenerator.h"

#include "iostream"

namespace P6 {
	class PhysicsWorld {
	
	//FIELDS
	private:
		GravityForceGenerator Gravity = GravityForceGenerator(MyVector(0, -9.8, 0));

	public:
		ForceRegistry forceRegistry;
		std::list<P6Particle*> Particles;

	//METHODS
	public:
		void AddParticle(P6Particle* toAdd);
		void Update(float time);
		void CheckLifespan(float time);

	private:
		void UpdateParticleList();
	};
}
