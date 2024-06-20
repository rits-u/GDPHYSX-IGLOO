#pragma once

#include "MyVector.h"
#include "chrono"

namespace P6 {

	class P6Particle
	{
		public:
			float mass = 0;
			MyVector Position;
			MyVector Velocity;
			MyVector Acceleration;
			float damping = 0.9f;
			float lifespan = 10.0f;
			//std::chrono::seconds lifespan;

		protected:
			MyVector accumulatedForce = MyVector(0, 0, 0);

			bool isDestroyed = false;

		public:
			P6Particle(MyVector Position, MyVector Velocity, MyVector Acceleration, float lifespan);

		protected:
			void UpdatePosition(float time);
			void UpdateVelocity(float time);
			

		public:
			void Update(float time);
			void Destroy();
			bool IsDestroyed();
			void AddForce(MyVector force); //adds force to particle
			void ResetForce();
			
			float getPosition(); //FOR DEBUG ONLY
	};
}

