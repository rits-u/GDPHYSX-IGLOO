#pragma once

#include "P6Particle.h"
#include "../Model/Model3D.h"

namespace P6 {
	using namespace model;

	class RenderParticle
	{
		public:
			P6Particle* physicsParticle;
			Model3D* renderObject;

		public:
			RenderParticle(P6Particle* p, Model3D* model);

			void draw();
	};

}

