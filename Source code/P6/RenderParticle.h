#pragma once

#include "P6Particle.h"
#include "../Model/Model3D.h"

namespace P6 {
	using namespace model;

	class RenderParticle
	{
		//FIELDS
	public:
		P6Particle* physicsParticle;
		Model3D* renderObject;
		MyVector Scale;

		//CONSTRUCTOR
	public:
		RenderParticle(P6Particle* p, Model3D* model);

		//METHODS
		void draw();
	};

}

