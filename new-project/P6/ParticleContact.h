#pragma once
#include "P6Particle.h"
#include "iostream"

namespace P6 {
	class ParticleContact
	{
	public:
		float depth; //interpenetration depth

		P6Particle* particles[2];
		float restitution;
		MyVector contactNormal;

		void Resolve(float time);

		float GetSeparatingSpeed();

	protected:

		void ResolveInterpenetration(float time);
		void ResolveVelocity(float time);
	};

}

