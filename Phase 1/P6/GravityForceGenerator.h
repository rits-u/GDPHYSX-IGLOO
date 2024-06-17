#pragma once
#include "ForceGenerator.h"

namespace P6 {
	class GravityForceGenerator : public ForceGenerator
	{

		private:
			//acceleration due to gravity
			MyVector Gravity = MyVector(0, -9.8f, 0); //9.8 m/s^2

		public:
			GravityForceGenerator(const MyVector gravity) : Gravity(gravity) {};
			void UpdateForce(P6Particle* particle, float time) override;
	};

}

