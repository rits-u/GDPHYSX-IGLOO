#pragma once

#include "../Springs/AnchoredSpring.h"
#include "Rod.h"
#include "../PhysicsWorld.h"

namespace P6 {
	class Cable : public ParticleLink
	{
		//attributes
		public:
			P6Particle* anchorParticle;
			float maxLength;
			float length;
			float restitution; 

		//constructor and method(s)
		public:
			Cable(P6Particle* p, float maxLength); 
			ParticleContact* GetContact() override;
	};

}
