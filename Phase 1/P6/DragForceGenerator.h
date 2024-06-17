#pragma once

#include "ForceGenerator.h"

namespace P6 {

	class DragForceGenerator : public ForceGenerator
	{
		private:
			//first coefficient of Friction
			float k1 = 0.74;
			//second coefficient of Friction
			float k2 = 0.57;

		public:
			DragForceGenerator() {}
			DragForceGenerator(float _k1, float _k2) : k1(_k1), k2(_k2) {}

			void UpdateForce(P6Particle* particle, float time) override;
	};

}
