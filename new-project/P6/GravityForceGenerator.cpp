#include "GravityForceGenerator.h"
using namespace P6;

//this function is used for applying gravity to the particle
void GravityForceGenerator::UpdateForce(P6Particle* particle, float time)
{
	if (particle->mass <= 0) return;

	//			F       A    *       m
	MyVector force = Gravity * particle->mass;
	particle->AddForce(force);
}