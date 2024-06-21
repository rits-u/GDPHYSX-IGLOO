#pragma once

#include "P6Particle.h"
#include "ForceGenerator.h"
#include "list"

namespace P6 {
	class ForceRegistry
	{
		//FIELDS
		protected:
			struct ParticleForceRegistry {
				P6Particle* particle;
				ForceGenerator* generator;
		};

		std::list<ParticleForceRegistry> Registry;

		//METHODS
		public:
			void Add(P6Particle* particle, ForceGenerator* generator);
			void Remove(P6Particle* particle, ForceGenerator* generator);
			void Clear();

			void UpdateForces(float time);

		
	};

}
