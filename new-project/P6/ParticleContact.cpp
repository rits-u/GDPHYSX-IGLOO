#include "ParticleContact.h"
using namespace P6;

void ParticleContact::ResolveInterpenetration(float time) {
	if (depth <= 0)
		return;

	//get the total mass of the collision
	float totalMass = (float)1 / particles[0]->mass;
	if (particles[1])
		totalMass += (float)1 / particles[1]->mass;

	if (totalMass <= 0) // invalid collision if total mass is 0 or less
		return;

	//check how much we move the particles
	//the higher the mass, the less the particle will move
	float totalMoveByMass = depth / totalMass;

	//the move position
	MyVector moveByMass = contactNormal * totalMoveByMass;

	//get the change in position for A
	MyVector P_a = moveByMass * ((float)1 / particles[0]->mass);
	particles[0]->Position += P_a; //translate

	if (particles[1]) {
		//get the change in position for B in the opposite direction (that's why it needs to be multiplied by -1)
		MyVector P_b = moveByMass * (-(float)1 / particles[1]->mass);
		particles[1]->Position += P_b;
	}

	depth = 0; //after solving, assume its depth now 0
}

float ParticleContact::GetSeparatingSpeed() {
	MyVector velocity = particles[0]->Velocity;
	if (particles[1]) {
		velocity -= particles[1]->Velocity;

		//N
		//MyVector position = particles[0]->Position - particles[1]->Position;
		//contactNormal = position.getDirection();
	}

	return velocity.scalarProduct(contactNormal);
}

void ParticleContact::ResolveVelocity(float time) {
	//sS
	float separatingSpeed = GetSeparatingSpeed();

	if (separatingSpeed > 0) {
		return;
	}

	float newSS = -restitution * separatingSpeed;
	float deltaSpeed = newSS - separatingSpeed;  //magnitude of delta velocity

	//get the total inverse mass of the colliding particles
	float totalMass = (float)1 / particles[0]->mass;
	if (particles[1])
		totalMass += (float)1 / particles[1]->mass;

	if (totalMass <= 0)
		return;

	float impulse_mag = deltaSpeed / totalMass;
	MyVector Impulse = contactNormal * impulse_mag;

	MyVector V_a = Impulse * ((float)1 / particles[0]->mass);
	//MyVector velocity = 
	particles[0]->Velocity = particles[0]->Velocity + V_a;

	if (particles[1]) {
		MyVector V_b = Impulse * ((float)-1 / particles[1]->mass);
		particles[1]->Velocity = particles[1]->Velocity + V_b;
	}
}

void ParticleContact::Resolve(float time) {
	//solve for the the V after collision
	ResolveVelocity(time);

	//solve for the pos after collision
	ResolveInterpenetration(time);
	//	std::cout << "aaa" << std::endl;

		//the two functions are interchangeable	
}