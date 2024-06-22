#include "DragForceGenerator.h"
using namespace P6;

//this method is used for applying drag or to slow down a particle
void DragForceGenerator::UpdateForce(P6Particle* particle, float time)
{
	MyVector force = MyVector(0, 0, 0);
	MyVector currV = particle->Velocity;


	//magnitude of velocity
	float mag = currV.getMagnitude();
	if (mag <= 0) return; //if di gumagalaw

	//Df        =  k1 * m    +  k2 * m
	float dragF = (k1 * mag) + (k2 * mag);
	MyVector dir = currV.normalize(); 

	particle->AddForce(dir * -dragF);
}