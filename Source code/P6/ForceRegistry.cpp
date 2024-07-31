#include "ForceRegistry.h"
using namespace P6;

//this function handles the registration of particle and the type of generator associated with it
void ForceRegistry::Add(P6Particle* particle, ForceGenerator* generator)
{
	ParticleForceRegistry toAdd;

	toAdd.particle = particle;
	toAdd.generator = generator;

	Registry.push_back(toAdd);
}

//this function removes the registered particle from the list
void ForceRegistry::Remove(P6Particle* particle, ForceGenerator* generator)
{
	Registry.remove_if(

		[particle, generator](ParticleForceRegistry reg) {
			return reg.particle == particle && reg.generator == generator;
		}
	);
}

//this function empties out the force registry
void ForceRegistry::Clear()
{
	Registry.clear();
}

//this function manages the update of the registered force
void ForceRegistry::UpdateForces(float time)
{
	for (std::list<ParticleForceRegistry>::iterator i = Registry.begin();
		i != Registry.end();
		i++) {

		i->generator->UpdateForce(i->particle, time);
	}
}


