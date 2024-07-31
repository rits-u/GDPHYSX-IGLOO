#pragma once

#include "../ForceGenerator.h"

namespace P6 {
	class ParticleSpring : public ForceGenerator
	{
	public:
		ParticleSpring(P6Particle* particle, float _springConst, float _restLen) :
			otherParticle(particle), springConstant(_springConst), restLength(_restLen) {}

		void UpdateForce(P6Particle* particle, float time) override;

	private:
		//this is where the spring is attached
		P6Particle* otherParticle;

		float springConstant; //how hard your spring is

		float restLength; //length of the spring at rest
	};

}

