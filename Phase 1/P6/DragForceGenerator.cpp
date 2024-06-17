#include "DragForceGenerator.h"
#include "iostream"

namespace P6 {
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

		std::cout << "HELLO?" << std::endl;

	}
}