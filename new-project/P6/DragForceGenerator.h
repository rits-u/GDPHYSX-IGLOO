#pragma once

#include "ForceGenerator.h"

namespace P6 {

	class DragForceGenerator : public ForceGenerator
	{
		//FIELDS
	private:
		//first coefficient of Friction
		float k1 = 0.74;
		//second coefficient of Friction
		float k2 = 0.57;

		//CONSTRUCTOR
	public:
		DragForceGenerator() {}
		DragForceGenerator(float _k1, float _k2) : k1(_k1), k2(_k2) {}

		//METHODS
	public:
		void UpdateForce(P6Particle* particle, float time) override;
	};

}
